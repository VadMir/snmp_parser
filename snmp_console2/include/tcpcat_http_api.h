/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/* AVOID THE UNICODE FORMAT! !NOTE! AVOID THE UNICODE FORMAT! */
/// \file tcpcat_http_api.h
/// \mainpage
/// @{
/// \section attention Предупреждение
/// \b ВНИМАНИЕ! Файл <b>"tcpcat_http_api.h"</b> распространяется под авторским правом РАЗРАБОТЧИКА данного файла.
/// Любые изменения в данном файле СТОРОННИМИ разработчиками НЕДОПУСТИМЫ.
/// Для использования данного файла просто включите его в проект с помощью директивы #include.
///
/// \section common Общие требования к плагинам
///   - плагины должны быть выполнены в виде динамически исполняемых библиотек (DLL)
///   - DLL-модули могут иметь любое имя и расширение ".dll"
///   - DLL-модули должны быть расположены в каталоге "<каталог EXE-модуля>\plugins" или
///       в его подкаталогах любого уровня вложения
///   - функции, экспортируемые библиотекой, должны иметь недекорируемые (naked) имена
///   - функции, экспортируемые библиотекой, должны поддерживать MSCU_CALL_PREFIX - stdcall (__stdcall) соглашение о вызове
///
/// \section changelog Изменения
/// - [+] 2016-05-13 - Добавлено: параметры raw_buf, raw_len в фунциию plug_http_session_data - !несовместимо с предыдущими версиями!
/// - [+] 2016-02-02 - Добавлено: возвращаемое значение TCPCAT_RESULT_ESCAPE_REST (см. описание)
/// - [*] 2015-07-30 - структура Ttcpcat_http_header: добавлены поля <tv_start>, <tv_stop> - !совместимость только по возрастанию!
/// - [+] 2015-02-17 - добавлено: флаг PERFORM_COMMAND_BIND для функции Ttcpcat_plug_http_perform (см. документацию)
/// - [+] 2015-02-17 - добавлено: флаг PERFORM_COMMAND_BUILD для функции Ttcpcat_plug_http_perform (см. документацию)
/// - [*] 2014-07-01 - структура Ttcpcat_http_header: добавлены поля <header_index>, <stub_0>, <raw_header_bytes>, <raw_header_size> - !совместимость только по возрастанию!
/// - [*] 2014-02-21 - структура Ttcpcat_http_header: добавлено поле <version>, изменена размерность полей <method>, <status_code> - !несовместимо с предыдущими версиями!
/// - [*] 2014-02-04 - Изменено: формат вызова функции Tplug_callback_is_native_url - добавлен новый параметр proto;
/// - [*] 2014-02-04 - Изменено: формат параметра natve_urls функции Tplug_http_register;
/// - [+] 2012-06-15 - добавлено - рекомендации по использованию атрибута PROTOCOL параметра data_attrs функции plug_callback_register_data (алгоритм работы, пункт 5)
/// - [+] 2012-04-02 - структура Ttcpcat_http_header: добавлено поле <referer>
/// - [*] 2012-02-20 - добавлена структура TTCPCATHttpStandardFunctions (параметр для функции tcpcat_plug_http_register)
/// - [*] 2012-02-17 - обновление интерфейса
/// - [*] 2012-02-16 - обновление документациии
/// - [*] 2012-02-13 - alpha-версия
///
/// \section copyright Авторские права
/// Copyright (C) MSC, ORG 2006-2016
///
/// @}
#ifndef TCPCAT_PLUG_HTTP_IF_INC
/// \cond
#define TCPCAT_PLUG_HTTP_IF_INC
/// \endcond

#include "mscu_types.h"
#include <limits.h>
#include <prefs/prefs.h>
#include <teri_bis/teri_bis.h>
#include "swine_api.h"
#include "tcpcat_api.h"

/// \page Algorithm Алгоритм работы сервера плагинов
/// @{
///
/// 1. После запуска сервер сканирует подкаталог "plugins" каталога, где расположен exe-файл (включая
///    подкаталоги), на предмет наличия dll-файлов с расширением ".dll". Очередной найденный файл
///    загружается и в нем проверяется наличие определенных экспортируемых функций
///      - tcpcat_plug_http_register        - тип \ref Tplug_http_register
///      - tcpcat_plug_http_config_register - тип \ref Tplug_http_config_register (не обязательно)
///      - tcpcat_plug_http_session_begin   - тип \ref Tplug_http_session_begin
///      - tcpcat_plug_http_session_data    - тип \ref Tplug_http_session_data
///      - tcpcat_plug_http_session_end     - тип \ref Tplug_http_session_end
///      - tcpcat_plug_http_perform         - тип \ref Ttcpcat_plug_http_perform
///      .
/// Далее:
///      Вызывается функция \b tcpcat_plug_http_register. Если функция возвратила нулевое значение (успех),
///      плагин заносится в список плагинов-обработчиков сервера. В случае неудачи модуль выгружается.
///
/// 2. После загрузки всех плагинов для каждого вызывается функция \b tcpcat_plug_http_config_register, предлагая плагину
///    зарегистрировать свои параметры работы (загрузка, модификация и сохрание параметров осуществляются вызывающим приложением).
///
/// 3. При изменении параметров работы системы (настройки параметров работы сервера) для каждого из плагинов
///    могут быть изменены параметры, зарегистрированные функцией tcpcat_plug_http_config_register
///    для вывода диалога изменения параметров. Диалог
///    изменения параметров должен полностью контролироваться (создаваться, удаляться) самим плагином.
///    Сервер не накладывает никаких ограничений на вид, струтуру и поведение данного диалога.
///
/// 4. Перед началом процесса обработки:
///     - Для каждого плагина-обработчика вызывается функция \b tcpcat_plug_http_perform(PERFORM_COMMAND_START) (для инициализации
///       внутренних структур).
///
/// 5. Процесс обработки.
///     - В процессе обработки при открытии очередной сессии поочередно для каждого плагина вызывается функция
///       \b tcpcat_plug_http_session_begin, предлагая плагину создать собствненный контекст обработки сессии.
///     - В процессе обработки, при поступлении очередного полного заголовка HTTP,
///       вызывается функция \b tcpcat_plug_http_session_data всех плагинов поочередно согласно списка.
///       Первый плагин, вернувший значение, отличное от TCPCAT_RESULT_ESCAPE, считается обработчиком для текущего заголовка и его данных.
///       Если плагин возвращает TCPCAT_RESULT_ESCAPE_REST, то он отказывается от как текущего заголовка с данными, так от всех остальных
///       в пределах данной TCP-сессии
///     - В процессе обработки, при поступлении очередных данных в рамках определенного заголовка HTTP,
///       вызывается функция \b tcpcat_plug_http_session_data соответствующего плагина с соответствующим контекстом обработки.
///       Значение, возвращаемое функцией, игнорируется.
///     - В процессе обработки, при завершении определенной сессии, вызывается функция \b tcpcat_plug_http_session_end
///       соответствующего плагина с соответствующим контекстом обработки для выполнения заключительных этапов
///       обработки и закрытия ресурсов, в том числе и самого контекста.
///     - В процессе обработки, когда входящая очередь пакетов пуста, с определенной
///       периодичностью (порядка 1 с) может вызываться функция \b tcpcat_plug_http_perform(PERFORM_COMMAND_IDLE), в которой плагин-обработчик может
///       выполнять фоновые операции.
///     - В процессе обработки может вызываться функция \b tcpcat_plug_http_perform, в которой плагин-обработчик должен
///       выполнять требуемые действия.
///     - С помощью klogf(msculib)  или Callback-функции \b plug_callback_add_message плагин-обработчик может послать сообщение серверу
///       для вывода его на экран пользователю. Сообщения могут быть различных типов: информация (MT_INFORMATION),
///       ошибка (MT_ERROR) и предупреждение (MT_WARNING).
///     - С помощью Callback-функции \b plug_callback_register_data плагин-обработчик может зарегистрировать определенный
///       блок выходных данных. Данные могут быть различного типа.
///       \b рекомендуется использовать атрибут PROTOCOL параметра data_attrs функции plug_callback_register_data для уточнения типа протокола
///       (должен содержать значения парметра short_name функции plug_http_register + два подчеркивания); например: "P:HTTP_WEBMAIL__"
///     - \b Внимание! Сервер ГАРАНТИРУЕТ, что вызов любой из экспортируемых плагинов функций для каждого плагина будет происходить синхронно, т.е.
///       в один и тот же момент времени будет выполняться только одна функция (без взаимных наложений)
///
/// 6. После завершения процесса обработки:
///     - для каждого плагина-обработчика вызывается функция \b tcpcat_plug_http_perform(PERFORM_COMMAND_FLUSH) - для "мягкого" завершения (с регистрацией неполных данных).
///     - для каждого плагина-обработчика вызывается функция \b tcpcat_plug_http_perform(PERFORM_COMMAND_STOP) - для "грубого" завершения.
///
/// @}

/// \defgroup Interface Интерфейс плагина-обработчика
/// @{

/// \name Коды типов HTTP-заголовков
/// \{

#define HTTP_METHOD_HTTP               0
#define HTTP_METHOD_GET                1
#define HTTP_METHOD_POST               2
#define HTTP_METHOD_CONNECT            3
#define HTTP_METHOD_HEAD               4
#define HTTP_METHOD_DELETE             5
#define HTTP_METHOD_PUT                6
#define HTTP_METHOD_TRACE              7
#define HTTP_METHOD_OPTION             8
#define HTTP_METHOD_PATCH              9
#define HTTP_METHOD_LINK              10
#define HTTP_METHOD_PROPFIND          11
#define HTTP_METHOD_PROPPATCH         12
#define HTTP_METHOD_MKCOL             13
#define HTTP_METHOD_COPY              14
#define HTTP_METHOD_MOVE              15
#define HTTP_METHOD_LOCK              16
#define HTTP_METHOD_UNLOCK            17
#define HTTP_METHOD_VERSION_CONTROL   18
#define HTTP_METHOD_CHECKOUT          19
#define HTTP_METHOD_UNCHECKOUT        20
#define HTTP_METHOD_CHECKIN           21
#define HTTP_METHOD_UPDATE            22
#define HTTP_METHOD_LABEL             23
#define HTTP_METHOD_REPORT            24
#define HTTP_METHOD_MKWORKSPACE       25
#define HTTP_METHOD_MKACTIVITY        26
#define HTTP_METHOD_BASELINE_CONTROL  27
#define HTTP_METHOD_MERGE             28

/// \}

/// \name Коды версий HTTP-ответов
/// \{

#define HTTP_VERSION_1_0               0
#define HTTP_VERSION_1_1               1
#define HTTP_VERSION_OTHER             2

/// \}

/// \name HTTP-заголовок
/// \{

STRUCT_PACKED_BEGIN
struct STRUCT_PACKED_ATTRIBUTE Ttcpcat_http_header {
public:
  guint8 method;        // available values - HTTP_METHOD_XXX constants
  guint8 version;       // HTTP request/response version - HTTP_VERSION_XXX constants
  guint16 status_code;  // status code for the response - 1xx, 2xx, 3xx, 4xx, 5xx
  gpchar status_label;  // for the response - symbol definition right after status code
  gpchar uri;           // полная строка запроса; процентное кодирование не снято
  gpchar url;           // доменное имя до первого /; процентное кодирование снято
  gpchar urn;           // доменнное имя + уточняющий адрес до знака ?; процентное кодирование снято
  gpchar urn_params;    // строка запроса после знака ?; процентное кодирование снято
  gpchar content_type;
  gpchar content_type_raw;
  gpchar set_cookie_raw;
  gpchar cookie_raw;
  gpchar referer;
  gchar ext[PI_CONTENT_SIZE];
  gint64 data_size; // -1 - не определено
  gboolean connection_close;
  gboolean content_encoding_gzip;
  gboolean transfer_encoding_chunked;
  gboolean has_content_range;
  gint64 content_range_min;
  gint64 content_range_max;   // -1 means undefined/default value
	gint64 content_range_total;	// -1 means undefined/default value
  // следующие заголовки удаляются из обработки:
  //   accept, accept-charset, accept-encoding, accept-language, cache-control, date, expires, if-modified-since, keep-alive, last-modified, pragma, server, user-agent, via
  gsize_t headers_names_count;
  gpchar * headers_names;
  gsize_t headers_values_count;
  gpchar * headers_values;
  guint16 header_index; // absolute index (starting from 0) of the given header within whole transport (TCP) session
  guint16 stub_0;       // stub for byte alignment - for future use
  gpchar raw_header_bytes; // buffer, containing raw HTTP-header
  gsize_t raw_header_size; // size of bytes in buffer
	Ttimeval tv_start; // starting timestamp for corresponding data block
	Ttimeval tv_stop;	 // stopping timestamp for corresponding data block
};
STRUCT_PACKED_END

/// \}

/// \name Значения, возвращаемые \ref Ttcpcat_http_session_data
/// \{

#define TCPCAT_RESULT_SKIP_NEXT     -2147483646 ///< 0x80000002 - пропустить до конца текущего блока
#define TCPCAT_RESULT_FINISH_NEXT   -2147483645 ///< 0x80000003 - собрать до конца текущего блока
#define TCPCAT_RESULT_ESCAPE_REST   -2147483644 ///< 0x80000004 - отказаться от текущего блока и от всех остальных

/// \}

/// \defgroup tcpcat_http_callback Функции обратного вызова
/// \{

/// проверка типа URL
/// \param stuff - параметр, передаваемый при вызове функций \ref Tplug_http_register, и определяющий текущий контекст вызова
/// \param url - текстовое сообщение (строка с завершающим нулем)
/// \param proto - если параметр не равен 0, то по возможности в него записывается адрес на строку с завершающим нулем, содержащую название протокола (если названия нет, то параметру присваивается нулевой адрес)
///
/// \return 0, если URL не является \"родным\" для одного из зарегистрированных плагинов
/// \return ненулевое значение, если URL является \"родным\" для одного из зарегистрированных плагинов
///
typedef gboolean (MSCU_CALL_PREFIX * Tplug_callback_is_native_url)(void * stuff, gconstpchar url, gconstpchar * proto);

/// @}

/// \struct TTCPCATHttpStandardFunctions
/// набор стандартных функций обратного вызова
STRUCT_PACKED_BEGIN
struct STRUCT_PACKED_ATTRIBUTE TTCPCATHttpStandardFunctions {
  // размер структуры.
  // Плагин является совместимым с Сервером, если размер структуры в нем не больше, чем в приложении.
  // проверка внутри экспортируемой функции плагина plug_http_register должна иметь вид:
  //   assert(sizeof(TTCPCATHttpStandardFunctions) <= TCPCATHttpStandardFunctions->cbSize);
  unsigned int cbSize; ///< размер данной структуры

  /// \name функции общего назначения
  ///@{
  Tplug_callback_is_native_url           plug_callback_is_native_url;
  ///@}
};
/// указатель на структуру TTCPCATHttpStandardunctions
typedef TTCPCATHttpStandardFunctions* PTCPCATHttpStandardFunctions;
STRUCT_PACKED_END

/// \}

/// \defgroup tcpcat_exports Экспортируемые функции
/// \{
/// Данный раздлел описывате типы экспортируемых функций для реализации внутри плагина

/// регистратор нового обработчика: экспортное имя - \b "tcpcat_plug_register". <br>
/// функция должна заполнить следующие строковые буферы (каждый размером TCPCAT_STR_SIZE)
/// определенными значениями (строками с завершающим нулем, например, с помощью функции strncpy):
///   \c version, \c name, \c short_name. \c filter_name, \c description, \c native_urls
/// \param version - версия плагина (например, "0.4.1")
/// \param name -        "длинное" имя протокола, данные которого способен
///               обрабатывать данный плагин, например: "HyperText Transfer Protocol"
///               синтаксис - не ограничен, одна строка, желательно, длиной до 40-60 символов
/// \param short_name -  "короткое" имя протокола, данные которого способен
///               обрабатывать данный плагин, например: "HTTP"
///               синтаксис - не ограничен, прописные буквы, желательно одним-двумя короткими словами
/// \param filter_name - "внутреннее" имя протокола, данные которого способен
///               обрабатывать данный плагин, например: "http"
///               синтаксис - только строчные буквы и символы подчеркивания, желательно одним коротким словом
/// \param description - описание плагина (например, "Обработчик HTTP + WebMail. Обрабатываемые версии HTTP: 1.0, 1.1. Обработка WebMail - mail.ru и др.")
///               синтаксис - не ограничен, возможны символы возврата каретки и перевода строки (многострочное описание)
/// \param native_urls - список "родных" значений URL, соответствующих данному протоколу
///               формат: <значение>=<протокол>;<значение>=<протокол>;...<значение>=<протокол>, например: "id.rambler.ru=wmail_rambler;mail.rambler.ru=wmail_rambler;newmail.rambler.ru=wmail_rambler;vk.com=vk"
///               синтаксис: маска в формате ITF (см. itf_bis.pdf)
///
/// \param TCPCATStandartFunctions - адрес на структуру, содержащую адреса стандартных функций обратного вызова TCPCAT (TTCPCATStandartFunctions).
///   Необходимо запомнить во внутренней переменной адрес структуры стандартных функций (сама структура располагается
///     внутри ядра и хранится все время жизни процесса
///
/// \param TCPCATHttpStandardFunctions - адрес на структуру, содержащую адреса стандартных функций обратного вызова TCPCATHttp (TTCPCATHttpStandardFunctions).
///   Необходимо запомнить во внутренней переменной адрес структуры стандартных функций (сама структура располагается
///     внутри ядра и хранится все время жизни процесса
///
/// \param TCPCATStuff - первый параметр для стандартных функций обратного вызова TCPCAT, TCPCATHttp (TTCPCATStandartFunctions, TTCPCATHttpStandardFunctions).
///   Необходимо запомнить во внутренней переменной и использовать при вызове стандартных функций обратного вызова
///
/// \return возвращает 0 в случае успеха
/// \return если библиотека не смогла нормально загрузиться, должна возратить ненулевое значение, чтобы сервер выгрузил библиотеку
typedef int (MSCU_CALL_PREFIX * Tplug_http_register)(PTCPCATStandartFunctions TCPCATStandartFunctions, PTCPCATHttpStandardFunctions TCPCATHttpStandardFunctions, void * TCPCATStuff,
                                        char * version, char * name, char * short_name, char * filter_name, char * description, char * native_urls);

/// регистрация параметров настройки модуля: экспортное имя - \b "tcpcat_plug_config_register". <br>
///
/// \param owner - корневой узел настроек для данного модуля
///
/// \note при регистрации параметров необходимо использовать функции prefs_XXX (обратный вызов)
///
/// \return функция не возвращает значения
///
typedef void (MSCU_CALL_PREFIX * Tplug_http_config_register)(preference_p owner);

/// Открытие новой сессии: экспортное имя - \b "tcpcat_plug_session_begin". <br>
/// В данной функции плагину предлагается инициализировать контекст обработки новой сессии.
///
/// \param sid - идентификатор новой сессии (адреса и порты).
///       Рекомендуется сохранять данный параметр если в дальнейшем предполагается вызов \ref Tplug_callback_register_data
///       Экземпляр структуры TCatSID, на который указывает данный параметр, сохраняется в течение жизни самой сессии.
///       Если планируется использование данной структуры далее, необходимо провести ее клонирование с помощью соответстующей функции.
///
/// \return возвращаемое значение - контекст обработки - хранится сервером и используется для его передачи функциям плагина \ref Tplug_http_session_data, \ref Tplug_http_session_end
/// \return если обработчик не собирается работать с данной сессией, то должен вернуть значение nil (NULL)
///
typedef void * (MSCU_CALL_PREFIX * Tplug_http_session_begin)(TCatSID * sid);

/// обработка данных сессии: экспортное имя - \b "tcpcat_plug_session_data". <br>
///
/// \param[in] shandle - ссылка на контекст обработки (возвращается функцией \ref Tplug_session_begin)
/// \param[in] header - HTTP-заголовок
/// \param[in] prev_header - предыдущий HTTP-заголовок
/// \param[in] buf - буфер с данными - блок данных сессии
/// \param[in] len - длина буфера с данными
/// \param[in] offset - смещение данных из буфера buf относительно HTTP-заголовка
/// \param[in] more_data - флаг того, что блок данных сессии - не последний (возможны последующие вызовы данной функции для данного HTTP-заголовка)
/// \param[in] raw_buf - буфер с сырыми данными - блок данных сессии до снятия сжатия/кодирования
/// \param[in] raw_len - длина буфера с сырыми данными (до снятия сжатия/кодирования)
///
/// Особые случаи: вызов функции при buf==0, len==0 при отсутствии флага more_data означает, что сессия завершилась по завершающим
///   FIN/RST или таймауту, а не по закрытию источника данных.
/// Особые случаи: вызов функции при buf==0, len<0 при наличии флага more_data означает, сколько байт было реально пропущено
///   в данной сессии после прошлого вызова данной функции с возвращенным значением, равным TCPCAT_RESULT_SKIP_ALL или (len + TCPCAT_RESULT_SKIP_BASE).
///
/// Особые случаи (HTTP): вызов функции при buf==0, len==0, more_data != 0 означает объявление HTTP-заголовка, за которым, в следующем вызове, последует передача самих данных
///
/// \return возвращаемое значение (учитывается только при передаче самого HTTP-заголовка без данных)
///     - len (должен обработать все данные)
///     - TCPCAT_RESULT_FINISH_NEXT	(-2147483645) (0x80000003 в абсолютном значении)
///					приказ серверу собирать данные текущего HTTP-заголовка до конца (в данном направлении???), затем передать на обработку
///     - TCPCAT_RESULT_SKIP_NEXT		(-2147483646) (0x80000002 в абсолютном значении)
///					приказ серверу пропустить данные стекущего HTTP-заголовка до конца (в данном направлении???)
///               данная функция будет вызвана не более одного раза со значениями параметров buf==0, len<0 и наличии флага more_data, где len в абсолютном значении будет определять количество реально пропущенных байт
///     - TCPCAT_RESULT_SKIP_ALL		(-2147483647) (0x80000001 в абсолютном значении)
///					приказ серверу пропустить данные сессии до конца (в данном направлении???)
///					данная функция будет вызвана не более одного раза со значениями параметров buf==0, len<0 и наличии флага more_data, где len в абсолютном значении будет определять количество реально пропущенных байт
///     - TCPCAT_RESULT_DISCARD			(2147483647)  (0x7fffffff в абсолютном значении)
///					отказ от дальнейшей обработки данной сессии
///     - TCPCAT_RESULT_ESCAPE			(2147483646)  (0x7ffffffe в абсолютном значении)
///					отказ от дальнейшей обработки данного HTTP-заголовка в пользу другого обработчика
///			- TCPCAT_RESULT_ESCAPE_REST (-2147483644) (0x80000004 в абсолютном значении)
///					отказ от дальнейшей обработки как текущего HTTP-заголовка, так и всех оставшихся в пределах
///					данной TCP-сессии в пользу другого обработчика
///
typedef int (MSCU_CALL_PREFIX * Tplug_http_session_data)(gpointer * shandle, Ttcpcat_http_header * header, Ttcpcat_http_header * prev_header, gconstpchar buf, int len, int offset, gboolean more_data, gconstpchar raw_buf, int raw_len);

/// закрытие сессии: экспортное имя - \b "tcpcat_plug_session_end". <br>
/// \param shandle - контекст обработки (возвращается функцией \ref Tplug_session_begin)
///
/// Вызывается, когда необходимо закрыть контекст обработки завершенной сессии.
/// В данной функции плагину предлагается финализировать служебные
/// данные, освободить выделенную память и т.д.
///
typedef void (MSCU_CALL_PREFIX * Tplug_http_session_end)(void * shandle);

/// фоновая обработка: экспортное имя - \b "tcpcat_plug_perform". <br>
///
/// \param command - действие
///
/// Выполнение дествия (зависит от command)
///  - PERFORM_COMMAND_BUILD - вызывается для построения дополнительных элементов обработчиков (вызов функции register_field_info)
///  - PERFORM_COMMAND_BIND - вызывается для связывание обработчиков (вызов функции find_field_info)
///  - PERFORM_COMMAND_START - вызывается при запуске нового сеанса обработки
///  - PERFORM_COMMAND_STOP - вызывается при завершении очередного сеанса обработки
///  - PERFORM_COMMAND_IDLE - дает возможность модулю производить фоновую обработку (вызывается с периодом, равным 1 сек или 100 мсек)
///  - PERFORM_COMMAND_FLUSH - завершение обработки с регистрацией неполных данных ("мягкое" завершение)
///  - PERFORM_COMMAND_SUSPEND - приостановка обработки, резервирование временных меток
///  - PERFORM_COMMAND_RESUME - возобновление обработки, корректировка временных меток, зарезервированных при последнем PERFORM_COMMAND_SUSPEND
///
/// \return функция возвращает true в случае удачного выполнения, иначе - false (в таком случае необходимо с помощью plug_callback_add_message вывести сообщение, описывающее ошибку)
///
typedef gboolean (MSCU_CALL_PREFIX * Ttcpcat_plug_http_perform)(gint command);

/// \}

/// @}

#endif
