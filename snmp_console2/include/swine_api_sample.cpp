/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/*
 * last update: 2009-12-01
 * 
 * swine_api_sample.cpp : example of swine_api.h usage
 *
 * !ВНИМАНИЕ! Данный файл является только примером использования swine_api.h.
 * Запрещается компилировать данный файл с исходным именем.
 * 
 * Copyright (C) MSC, ORG 2006-2009
 */

#include <swine_api.h>
#include <swine_utils.h>

// Now we use the generic helper definitions above to define XXX_API and XXX_LOCAL.
// XXX_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// XXX_LOCAL is used for non-api symbols.
#ifdef SWINE_API_SAMPLE_EXPORTS // defined if we are building the XXX DLL (instead of using it)
  /// \cond
  #define SWINE_API_SAMPLE_API MSCU_HELPER_DLL_EXPORT
  /// \endcond
#else
  /// \cond
  #define SWINE_API_SAMPLE_API MSCU_HELPER_DLL_IMPORT
  /// \endcond
#endif // SWINE_API_SAMPLE_EXPORTS
#define SWINE_API_SAMPLE_LOCAL MSCU_HELPER_DLL_LOCAL

//////////////////////////////////////////////////////////////////////////
PSWINEStandartFunctions swine; // глобальный указатель на стандартные функции (данный указатель используется в swine_utils.h)

//////////////////////////////////////////////////////////////////////////
void register_kermit();

//////////////////////////////////////////////////////////////////////////
// экспортируемая функция - имя без декорирования
SWINE_API_SAMPLE_API void MSCU_CALL_PREFIX swine_plugin_init(TSWINEStandartFunctions * SWINEStuff, gpchar adescription, gpchar aversion)
{
  /* запоминаем адрес структуры стандартных функций */
  assert(sizeof(TSWINEStandartFunctions) <= SWINEStuff->cbSize);
  swine = SWINEStuff;
  /* передаем свои описание и версию */
  strncpy(adescription	, "SWINE plugin sample"	, SWINE_STR_SIZE);
  strncpy(aversion		, "0.1.1"				, SWINE_STR_SIZE);

  // регистрируем обработчик
  register_kermit();
}

//////////////////////////////////////////////////////////////////////////
static guint WTAP_ENCAP_KERMIT = 0; // сеть передачи данных для связи декодера с обработчиком протокола

guint cfg_kermit_stream_synch_count = 8; // параметр

gboolean cfg_kermit_enable_compression = false; // параметр - используется сжатие или нет

//////////////////////////////////////////////////////////////////////////
static PProtoReg         proto_kermit_stream = 0;
static PProtoReg         proto_kermit = 0;

// декодер
class LOCAL_API Tproto_kermit_stream: public TIProto {
public:
  Tproto_kermit_stream(PPluginProtoStuff stuff): TIProto(stuff) 
  {
  }

  virtual ~Tproto_kermit_stream() {};

  gboolean perform(gint command)
  {
    switch (command) {
    case PERFORM_COMMAND_BUILD:
      set_network(WTAP_ENCAP_KERMIT); // установка сети передачи данных для данного декодера
      break;
    case PERFORM_COMMAND_BIND:
      break;
    case PERFORM_COMMAND_START:
      // очищаем входной буфер
      for (gint i = 0; i < P2P_DIR_COUNT; ++i) {
        InitBuf(i);
        Fp2p[i].Fsynch_count = 0;
      }
      break;
    case PERFORM_COMMAND_STOP:
      break;
    case PERFORM_COMMAND_START_TEST:
      // очищаем входной буфер
      for (gint i = 0; i < P2P_DIR_COUNT; ++i) {
        InitBuf(i);
        Fp2p[i].Fsynch_count = 0;
      }

      in_test_ = true; // запоминаем, что мы в режиме теста
      break;
    case PERFORM_COMMAND_STOP_TEST:
      in_test_ = false;
      break;
    case PERFORM_COMMAND_IDLE:
      break;
    case PERFORM_COMMAND_FLUSH:
      break;
    case PERFORM_COMMAND_SUSPEND:
      break;
    case PERFORM_COMMAND_RESUME:
      break;
    }
    return true;
  }

  // обработка
  void crop(tvbuff_t* tvb, PPacketInfo pi, PkrTreeNode tree) 
  {
    if (tree)
      return;

    tvbuff_t tvb_;
    PPacketInfo my_pi;

    gint dir = pi->p2p_dir; // работаем по определенному направлению
    for (guint i = 0; i < tvb->len; ++i) {
      Fp2p[dir].FInByte = tvb->buf[i];
      switch (Fp2p[dir].FStateType) {
        ...
        my_pi = packet_info_clone(pi); // клонируем информацию о пакете
        if (CalcCheckSum(dir) == (Fp2p[dir].FData[Fp2p[dir].FPacketLen - 2] - KERMIT_SP)) 
          my_pi->crctype = CRC_OK;
        else
          my_pi->crctype = CRC_BAD;
        if (in_test_) {
          ...
          ack_frame(0, my_pi); // регистрируем факт выделения кадра из потока
          ...
        } else {
          ...
          ack_frame(tvb_set_buf(&tvb_, Fp2p[dir].FData, Fp2p[dir].FPacketLen), my_pi); // регистрируем очередной кадр - передаем обработчику протокола
          ...
        }
        ...
        packet_info_free(my_pi);
        ...
      default:
        ...
      }
    }
  }

  struct {
    guint8 FData[KERMIT_MAX_PACKET];
    gint FDataLen;
    gint FDataLenNeeded;
    guint8 FInByte;
    gint FPacketLen;
    TStateType FStateType;
    gint Fsynch_count;
  } Fp2p[P2P_DIR_COUNT]; // состояние обработки по каждому направлению

  gboolean in_test_;
};

class LOCAL_API Tproto_kermit: public TIProto {
public:
  Tproto_kermit(PPluginProtoStuff stuff): TIProto(stuff) 
  {
    for (gint i = 0; i < P2P_DIR_COUNT; ++i) { // устанвливаем параметры по умолчанию
      Fp2p[i].FHasPackets  = false;
      Fp2p[i].FSData = "";
      Fp2p[i].FSFileName = "";
      Fp2p[i].Fpi = 0;
    }
  }

  virtual ~Tproto_kermit() {};

  gboolean perform(gint command){
    switch (command) {
    case PERFORM_COMMAND_BUILD:
      break;
    case PERFORM_COMMAND_BIND:
      // регистрируемся на самом низком уровне по соответствующей сети передачи данных - связываемся с декодером
      dissector_add("wtap_encap", WTAP_ENCAP_KERMIT); 
      // !для эвристсических обработчиков!
      (*swine->plug_proto_heur_dissector_add)(stuff, "ip.raw"); // зарегистрироваться эвристическим обработчиком для IP-пакетов (вместе с заголовком IP-пакета)
      break;
    case PERFORM_COMMAND_START:
      for (gint i = 0; i < P2P_DIR_COUNT; ++i) { // устанвливаем параметры по умолчанию
        Fp2p[i].FKermitState.MaxPacketSize = KERMIT_MAX_PACKET;
        Fp2p[i].FKermitState.MaxWaitSecs = 0x25;
        Fp2p[i].FKermitState.Staffings = 0;
        Fp2p[i].FKermitState.StaffingByte = 0;
        Fp2p[i].FKermitState.EOHByte = 0x0D;
        Fp2p[i].FKermitState.PrefixByte = '#';
        Fp2p[i].FHasPackets = false;
      }
      break;
    case PERFORM_COMMAND_STOP:
      for (gint i = 0; i < P2P_DIR_COUNT; ++i) { // устанвливаем параметры по умолчанию
        if (Fp2p[i].Fpi != 0) {
          packet_info_free(Fp2p[i].Fpi);
          Fp2p[i].Fpi = 0;
        }
      }
      break;
    case PERFORM_COMMAND_START_TEST:
      break;
    case PERFORM_COMMAND_STOP_TEST:
      break;
    case PERFORM_COMMAND_IDLE:
      // проверяем таймауты - если вышли - регистрируем данные
      for (gint i = 0; i < P2P_DIR_COUNT; ++i) {
        if (Fp2p[i].FSData.size() == 0)
          continue;
        guint ButNow = mscu_global_msecs;
        if (((ButNow - Fp2p[i].FLastPacketTime) / 1000) > Fp2p[i].FKermitState.MaxWaitSecs) 
          PostSession(i);
      }
      break;
    case PERFORM_COMMAND_FLUSH:
      // регистрируем данные
      for (gint i = 0; i < P2P_DIR_COUNT; ++i) 
        PostSession(i);
      break;
    case PERFORM_COMMAND_SUSPEND:
      break;
    case PERFORM_COMMAND_RESUME:
      break;
    }
    return true;
  }

  void crop(tvbuff_t* tvb, PPacketInfo pi, PkrTreeNode tree) {
    if (tree)
      return;

    PPacketInfoEx pi_ex;
    gchar sbuf[2048];

    if (pi->crctype == CRC_BAD) { // если контрольная сумма неверная
      pi_ex = packet_info_ex_malloc();
      pi->genre = PG_BAD; // указываем, что пакет плохой
      packet_info_ex_set_description(pi_ex, "плохой CRC");
      ack_ex(tvb, pi, pi_ex); // регистрируем
      return;
    }
    if (tvb->len < 6) { // проверяем на минимум размера пакета
      pi_ex = packet_info_ex_malloc();
      pi->genre = PG_BAD; // указываем, что пакет плохой
      packet_info_ex_set_description(pi_ex, "неверная длина");
      ack_ex(tvb, pi, pi_ex); // регистрируем
      return;
    }
    ...
    PPacketInfoEx pi_ex = packet_info_ex_malloc();
    packet_info_ex_set_generic_name(pi_ex, Fp2p[Direction].FSFileName.c_str()); // оригинальное имя передаваемого файла
    sprintf_s(sbuf, sizeof(sbuf), "файл: %s", pi_ex->generic_name);
    packet_info_ex_set_description(pi_ex, sbuf);
    tvbuff_t tvb;
    // регистрируем данные
    ack_ex(tvb_set_buf(&tvb, (guint8*)Fp2p[Direction].FSData.c_str(), Fp2p[Direction].FSData.size()), Fp2p[Direction].Fpi, pi_ex);
    packet_info_free(Fp2p[Direction].Fpi);
    Fp2p[Direction].Fpi = 0;
    ...
  }

  // !для эвристсических обработчиков!
  gboolean heur(tvbuff_t* tvb, PPacketInfo pi)
  {
    // вернуть true, если пакет опознан, false, если пакет нужно (можно отдать другим обработчикам)
  }


  struct {
    gboolean FHasPackets;
    TKermitState FKermitState;
    guint FLastPacketNumber;
    guint FLastPacketTime;
    string FSData;
    string FSFileName;
    TPostState FPostState;
    gint FRepeatCount;
    PPacketInfo Fpi;
  } Fp2p[P2P_DIR_COUNT]; // состояние обработки по каждому направлению
};

// регистрируемый класс функций обработчика
static TPluginProtoClass class_kermit_stream = {
  &tmpl_proto_create<Tproto_kermit_stream>,
  &tmpl_proto_destroy<Tproto_kermit_stream>, 
  &tmpl_proto_perform<Tproto_kermit_stream>, 
  &tmpl_proto_crop<Tproto_kermit_stream>, 
  0, 0
};  

// регистрируемый класс функций обработчика
static TPluginProtoClass class_kermit = {
  &tmpl_proto_create<Tproto_kermit>,
  &tmpl_proto_destroy<Tproto_kermit>, 
  &tmpl_proto_perform<Tproto_kermit>, 
  &tmpl_proto_crop<Tproto_kermit>, 
  &tmpl_proto_heur<Tproto_kermit>, 
  0
};

void register_kermit()
{
  // регистрируем собственную сеть передачи данных
  WTAP_ENCAP_KERMIT = (*swine->wtap_encap_register)("KERMIT", "kermit");

  // регистрируем декодер
  proto_kermit_stream = (*swine->plug_deco_register_decoder)(
    "KERMIT", "KERMIT", "stream_kermit",
    "Декодер потока канального уровня передачи файлов KERMIT.\n"
    "Регистрирует в таблице \"wtap_encap\" значение \"kermit\".\n"
    "Использует сетевой уровень \"wtap_encap\" со значением \"kermit\".\n"
    , &class_kermit_stream);
  // получаем корнневой узел в дереве параметров
  preference_p pref_kermit_stream = (*swine->plug_prefs_register_decoder)(proto_kermit_stream);
  // регистрируем параметр
  prefs_register_uint_preference(pref_kermit_stream, 0, 0, 0, "kermit_stream_synch_count",
    "Синхронизация, пакеты",
    "Количество корректных пакетов, идущих подряд и опознанных декодером. \n"
    "Если найдено данное количество пакетов, считается, что синхронизация декодера произведена, т.е. деодер \"опознал\" поток. \n"
    "При нулевом значении синхронизация не производится. \n"
    ,&cfg_kermit_stream_synch_count);

  // регистрируем обработчик протокола
  proto_kermit = (*swine->plug_proto_register_protocol)(
    "KERMIT", "KERMIT", "kermit",
    "Протокол канального уровня передачи файлов.\n"
    "Регистрирует обработчик \"kermit\".\n"
    "Регистрирует в таблице \"wtap_encap\" значение \"kermit\".\n"
    "Регистрируется в таблице \"wtap_encap\" со значением \"kermit\".\n"
    , &class_kermit);
  // получаем корнневой узел в дереве параметров
  preference_p pref_kermit = (*swine->plug_prefs_register_protocol)(proto_kermit);
  // регистрируем параметр
  prefs_register_bool_preference(pref_kermit, 0, 0, 0, "kermit_enable_compression",
    "Использовать сжатие",
    "Использовать сжатие в пакетах данных или нет: трактовать символ \"~\" как символ повторения или нет"
    ,&cfg_kermit_enable_compression);
}

