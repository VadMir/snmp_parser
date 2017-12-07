������ teri_bis_wrapper_compile:

1. ������� ���������� � ������� teri_bis_create

2. ������� ����� � ������, ���������� itf-������ (�����)
...

3. �������� teri_bis_generate (��. �������� �� ��� ������������ � ������� �������)
  !����� -  instance ������ � ������� teri_bis_create!

  _internal_res = teri_bis_generate(instance, 0, buf, len, check_only, teri_bis_wrapper_std_generate_callback, this);
  if (_internal_res != TERI_ERROR_SUCCESS) {
    _internal_res = teri_bis_get_error(instance, 0, 0, &_internal_err_str);
    mscu_throw_exception(str_format("��������� ������ ��������� ��������, ��� ������ : %d, ��������: \"%s\"", _internal_res, _internal_err_str));
  };

4. � ������ ����� ��������� ���������������� ������� � ����� �����

  buf2.resize(teri_bis_save(instance, 0, 0)); // �������� ������ ����������

  // ���������� � �����
  _internal_res = teri_bis_save(instance, (gpchar)&buf2[0], (gint)buf2.size());
  if (_internal_res < 0) {
    _internal_res = teri_bis_get_error(AEngine, 0, 0, &_internal_err_str);
    mscu_throw_exception(str_format("��������� ������ ���������� ��������, ��� ������ : %d, ��������: \"%s\"", _internal_err_str, _internal_res));
  }


5. ������� ���������� � ������� teri_bis_destroy

6. ��� ���������� ������� teri_bis_wrapper_std_generate_callback
  !��������. ��. �������� ������ - ��� �������, � ����� ��������� ����� ������ ������� ��������!

gboolean MSCU_CALL_PREFIX teri_bis_wrapper_std_generate_callback(gpointer user_data, gint32 Msg, guint32 wParam, guint32 lParam, gpchar MsgStr)
{
  gchar sbuf[2048];
  Tteri_bis_wrapper* instance = (Tteri_bis_wrapper*)user_data;
  switch (Msg) 
  {
  case CP_generate_ver_begin:
    instance->cb_generate_time = mscu_global_usecs_abs_0();
    sprintf_s(sbuf, sizeof(sbuf), "[%s] [%d/%d] �������� ���������...", instance->name.c_str(), (lParam & 0xff), (lParam >> 8));
    if (instance->log_progress)
      klog(sbuf, MT_PROGRESS_BEGIN);
    break;
  case CP_generate_ver_progress: 
    sprintf_s(sbuf, sizeof(sbuf), "%d%%", wParam);
    if (instance->log_progress)
      klog(sbuf, MT_PROGRESS);
    break;
  case CP_generate_ver_end: 
    instance->cb_generate_new_time = mscu_global_usecs_abs_0(); // stop time counter
    sprintf_s(sbuf, sizeof(sbuf), "�����: %s ���", fmt_num0(instance->cb_generate_new_time - instance->cb_generate_time).c_str()); // time elsapsed
    if (instance->log_progress)
      klog(sbuf, MT_PROGRESS_END); // time elsapsed
    break;
  case CP_generate_gen_begin: 
    instance->cb_generate_time = mscu_global_usecs_abs_0();
    sprintf_s(sbuf, sizeof(sbuf), "[%s] [%d/%d] �������� ��������...", instance->name.c_str(), (lParam & 0xff), (lParam >> 8));
    if (instance->log_progress)
      klog(sbuf, MT_PROGRESS_BEGIN);
    break;
  case CP_generate_gen_progress: 
    sprintf_s(sbuf, sizeof(sbuf), "%d%%", wParam);
    if (instance->log_progress)
      klog(sbuf, MT_PROGRESS);
    break;
  case CP_generate_gen_end: 
    instance->cb_generate_new_time = mscu_global_usecs_abs_0(); // stop time counter
    sprintf_s(sbuf, sizeof(sbuf), "�����: %s ���", fmt_num0(instance->cb_generate_new_time - instance->cb_generate_time).c_str()); // time elsapsed
    if (instance->log_progress)
      klog(sbuf, MT_PROGRESS_END); // time elsapsed
    break;
  case CP_generate_cmp_begin: 
    instance->cb_generate_time = mscu_global_usecs_abs_0();
    sprintf_s(sbuf, sizeof(sbuf), "[%s] [%d/%d] ������ ��������...", instance->name.c_str(), (lParam & 0xff), (lParam >> 8));
    if (instance->log_progress)
      klog(sbuf, MT_PROGRESS_BEGIN);
    break;
  case CP_generate_cmp_progress: 
    sprintf_s(sbuf, sizeof(sbuf), "%d%%", wParam);
    if (instance->log_progress)
      klog(sbuf, MT_PROGRESS);
    break;
  case CP_generate_cmp_end: 
    instance->cb_generate_new_time = mscu_global_usecs_abs_0(); // stop time counter
    sprintf_s(sbuf, sizeof(sbuf), "�����: %s ���", fmt_num0(instance->cb_generate_new_time - instance->cb_generate_time).c_str()); // time elsapsed
    if (instance->log_progress)
      klog(sbuf, MT_PROGRESS_END); // time elsapsed
    break;
  case CP_bis_generate_lod_begin: 
    instance->cb_generate_time = mscu_global_usecs_abs_0();
    sprintf_s(sbuf, sizeof(sbuf), "[%s] [%d/%d] ����� �������� ���������...", instance->name.c_str(), (lParam & 0xff), (lParam >> 8));
    if (instance->log_progress)
      klog(sbuf, MT_PROGRESS_BEGIN);
    break;
  case CP_bis_generate_lod_progress: 
    sprintf_s(sbuf, sizeof(sbuf), "%d%%", wParam);
    if (instance->log_progress)
      klog(sbuf, MT_PROGRESS);
    break;
  case CP_bis_generate_lod_end: 
    instance->cb_generate_new_time = mscu_global_usecs_abs_0(); // stop time counter
    sprintf_s(sbuf, sizeof(sbuf), "�����: %s ���", fmt_num0(instance->cb_generate_new_time - instance->cb_generate_time).c_str()); // time elsapsed
    if (instance->log_progress)
      klog(sbuf, MT_PROGRESS_END); // time elsapsed
    break;
  default:
    if (Msg < 0) { // error
      if (Msg > TERI_START_BASE_WARNING) { /* attention: degree >, because of negative values */
        sprintf_s(sbuf, sizeof(sbuf), "[%s] ��������� - ������: \"%s\". ���: %d, ���������: %d, %d.", instance->name.c_str(), MsgStr, Msg, wParam, lParam);
        klog(sbuf, MT_ERROR);
      } else {
        sprintf_s(sbuf, sizeof(sbuf), "[%s] ��������� - ��������������: \"%s\". ���: %d, ���������: %d, %d.", instance->name.c_str(), MsgStr, Msg, wParam, lParam);
        klog(sbuf, MT_WARNING);
      }
    } else if (Msg == 0) { 
      klogf(MT_INFORMATION, "[%s] %s", instance->name.c_str(), MsgStr);
    }
    break;
  }

  return (!kterm());
}

7. ����� (����� �������, ������ ������ teri_bis_match_start, teri_bis_match_data, teri_bis_match_stop)

  // ��������� ������ ������
  vector<gconstpchar> fixed_bufs;
  vector<gint32> fixed_lens;
  vector<guint32> fixed_spots;

  fixed_bufs.resize(4);
  fixed_lens.resize(4);
  fixed_spots.resize(4);

  // ������, � ������� ����
  fixed_bufs[0] = (gconstpchar) &sid->saddr.in_addr; // IPv4-�����
  fixed_bufs[1] = (gconstpchar) &sid->daddr.in_addr; // IPv4-�����
  fixed_bufs[2] = (gconstpchar) &sport; // TCP-����
  fixed_bufs[3] = (gconstpchar) &dport; // TCP-����

  // ����� �������
  fixed_lens[0] = 4;
  fixed_lens[1] = 4;
  fixed_lens[2] = 2;
  fixed_lens[3] = 2;

  // ���� ����� ������� (��� � ��� ����������)
  fixed_spots[0] = TERI_BIS_SPOT_bIS; 
  fixed_spots[1] = TERI_BIS_SPOT_bID;
  fixed_spots[2] = TERI_BIS_SPOT_bPS;
  fixed_spots[3] = TERI_BIS_SPOT_bPD;
 
  // �������� ������� ������ (����������� ���������� �� �����)
  gint result = teri_bis_match_medium_atomic_all_bufs(
      instance, 4,
      &fixed_bufs[0], &fixed_lens[0], &fixed_spots[0], 0,
      &teri_bis_match_callback_plug, &uin_store/*��� user_data*/);

  if (result > 0) {
    ++teri_bis_wrapper_tcpcat_plug_specialized_teri_statistics_->tokens_rdy; // ��� �����
  } else
    ++teri_bis_wrapper_tcpcat_plug_specialized_teri_statistics_->tokens_unk; // ������ �� ����

// ������� ��������� ������
static void MSCU_CALL_PREFIX teri_bis_match_callback_plug(gpointer ud, Pteri_bis_match_token token) 
{
  TPLUGUINStore * store = (TPLUGUINStore *) ud;
  ...
  if (cfg_tcpcat_plug_specialized_teri_consider_lid && (token->id != store->LID))
    return;
  ...
}

