#ifndef ___DMC5480_LIB_H
#define ___DMC5480_LIB_H

//��һ������Ķ�  //This segment should not be modified
#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/* Define NULL pointer value */

#ifndef NULL
#ifdef  __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif


typedef int                          BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef unsigned long		DWORD;                  
typedef float                       FLOAT;


#define __DMC5480_EXPORTS

//������������
#ifdef __DMC5480_EXPORTS
	#define DMC5480_API __declspec(dllexport)
#else
	#define DMC5480_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

//---------------------   �忨��ʼ�����ú���  ----------------------
/********************************************************************************
** ��������: d5480_board_init
** ��������: ���ư��ʼ�������ó�ʼ�����ٶȵ�����
** �䡡  ��: ��
** �� �� ֵ: 0���޿��� 1-8���ɹ�(ʵ�ʿ���) 
**     
*********************************************************************************/
DMC5480_API int __stdcall d5480_board_init(void);

/********************************************************************************
** ��������: d5480_board_close
** ��������: �ر����п�
** �䡡  ��: ��
** �� �� ֵ: ��
** ��    ��: 2007.02.1
*********************************************************************************/
DMC5480_API void __stdcall d5480_board_close(void); 

/********************************************************************************
** ��������: ���ƿ���λ
** ��������: ��λ���п���ֻ���ڳ�ʼ�����֮����ã�
** �䡡  ��: ����
** �� �� ֵ: ������
** ��    ��: 2007.02.1
*********************************************************************************/
DMC5480_API DWORD __stdcall d5480_board_reset(WORD card);

DMC5480_API DWORD __stdcall d5480_get_card_version(WORD card);
DMC5480_API DWORD __stdcall d5480_get_card_soft_version(WORD card, WORD* firm_id, DWORD* sub_firm_id);

DMC5480_API DWORD __stdcall d5480_get_client_ID(WORD card);

DMC5480_API DWORD __stdcall d5480_get_lib_version(void);
DMC5480_API DWORD __stdcall d5480_get_card_ID(WORD card);
DMC5480_API DWORD __stdcall d5480_get_total_axes(WORD card);
DMC5480_API DWORD __stdcall d5480_test_software(WORD card, WORD testid, WORD para1, WORD para2, WORD para3);
DMC5480_API DWORD __stdcall d5480_test_hardware(WORD card);
DMC5480_API DWORD __stdcall d5480_download_firmware(WORD card, const char* pfilename);


//���������������
DMC5480_API DWORD __stdcall d5480_set_pulse_outmode(WORD axis,WORD outmode);
DMC5480_API DWORD __stdcall d5480_counter_config(WORD axis,WORD mode);

//������ö�
DMC5480_API DWORD __stdcall d5480_get_pulse_outmode(WORD axis,WORD *outmode);
DMC5480_API DWORD __stdcall d5480_get_counter_config(WORD axis,WORD* mode);

DMC5480_API DWORD __stdcall d5480_get_config_SD_PIN(WORD axis,WORD *enable, WORD *sd_logic,WORD *sd_mode);
 
DMC5480_API DWORD __stdcall d5480_get_config_INP_PIN(WORD axis,WORD* enable,WORD* inp_logic);
DMC5480_API DWORD __stdcall d5480_get_config_ERC_PIN(WORD axis,WORD* enable,WORD* erc_logic,
				WORD* erc_width,WORD* erc_off_time);
DMC5480_API DWORD __stdcall d5480_get_config_ALM_PIN(WORD axis, WORD* enable, WORD* alm_logic,WORD* alm_action);
DMC5480_API DWORD __stdcall d5480_get_config_EL_PIN(WORD axis, WORD* el_logic, WORD* el_mode);

DMC5480_API DWORD __stdcall d5480_get_config_HOME_PIN_logic(WORD axis,WORD* org_logic,WORD* filter);
DMC5480_API DWORD __stdcall d5480_get_config_home_mode(WORD axis,WORD* home_dir, double* vel,WORD* home_mode,WORD* EZ_count);

DMC5480_API DWORD __stdcall d5480_get_handwheel_inmode(WORD axis, WORD * inmode, double* multi);

DMC5480_API DWORD __stdcall d5480_get_config_LTC_PIN(WORD axis,WORD* ltc_logic, WORD* ltc_mode);
DMC5480_API DWORD __stdcall d5480_get_config_latch_mode(WORD cardno, WORD* all_enable);


//ר���ź����ú���
DMC5480_API DWORD __stdcall d5480_config_SD_PIN(WORD axis,WORD enable, WORD sd_logic,WORD sd_mode);

DMC5480_API DWORD __stdcall d5480_config_INP_PIN(WORD axis,WORD enable,WORD inp_logic);
DMC5480_API DWORD __stdcall d5480_config_ERC_PIN(WORD axis,WORD enable,WORD erc_logic,
				WORD erc_width,WORD erc_off_time);

DMC5480_API DWORD __stdcall d5480_config_EMG_PIN(WORD cardno, WORD option, WORD emg_logic);
DMC5480_API DWORD __stdcall d5480_get_config_EMG_PIN(WORD cardno, WORD* enbale, WORD* emg_logic);

DMC5480_API DWORD __stdcall d5480_config_ALM_PIN(WORD axis, WORD enable, WORD alm_logic,WORD alm_action);
//new
DMC5480_API DWORD __stdcall d5480_config_EL_PIN(WORD axis, WORD el_logic, WORD el_mode);

DMC5480_API DWORD __stdcall d5480_config_HOME_PIN_logic(WORD axis,WORD org_logic,WORD filter);

DMC5480_API DWORD __stdcall d5480_write_SEVON_PIN(WORD axis, WORD on_off);
DMC5480_API int __stdcall d5480_read_SEVON_PIN(WORD axis);

DMC5480_API DWORD __stdcall d5480_write_ERC_PIN(WORD axis, WORD sel);
DMC5480_API int __stdcall d5480_read_RDY_PIN(WORD axis);

DMC5480_API DWORD __stdcall d5480_set_backlash(WORD axis, long backlash);
DMC5480_API DWORD __stdcall d5480_get_backlash(WORD axis, long* backlash);

//ͨ������/������ƺ���
DMC5480_API int __stdcall d5480_read_inbit(WORD cardno, WORD bitno);
DMC5480_API DWORD __stdcall d5480_write_outbit(WORD cardno, WORD bitno,WORD on_off);
DMC5480_API int __stdcall  d5480_read_outbit(WORD cardno, WORD bitno) ;
DMC5480_API long __stdcall d5480_read_inport(WORD cardno);
DMC5480_API long __stdcall d5480_read_outport(WORD cardno) ;
DMC5480_API DWORD __stdcall d5480_write_outport(WORD cardno, DWORD port_value);

//�ƶ�����
DMC5480_API DWORD __stdcall d5480_decel_stop(WORD axis,double dec);
DMC5480_API DWORD __stdcall d5480_imd_stop(WORD axis);
DMC5480_API DWORD __stdcall d5480_emg_stop(void) ;
DMC5480_API DWORD __stdcall d5480_simultaneous_stop(WORD axis) ;

//λ�����úͶ�ȡ����
DMC5480_API long __stdcall d5480_get_position(WORD axis);
DMC5480_API DWORD __stdcall d5480_set_position(WORD axis,long current_position);


//״̬��⺯��
DMC5480_API int __stdcall  d5480_check_done(WORD axis) ;
DMC5480_API DWORD __stdcall d5480_axis_io_status(WORD axis);


//�ٶ�����
DMC5480_API double __stdcall d5480_read_current_speed(WORD axis);
DMC5480_API double __stdcall d5480_read_vector_speed(WORD card);
DMC5480_API DWORD __stdcall d5480_change_speed(WORD axis,double Curr_Vel);

DMC5480_API DWORD __stdcall d5480_set_vector_profile(WORD cardno,double s_para, double Max_Vel, double acc,double dec );
DMC5480_API DWORD __stdcall d5480_get_vector_profile(WORD cardno,double* s_para, double* Max_Vel, double* acc,double* dec );

DMC5480_API DWORD __stdcall d5480_set_profile(WORD axis,double option,double Max_Vel,double acc,double dec);
DMC5480_API DWORD __stdcall d5480_set_s_profile(WORD axis,double s_para);

DMC5480_API DWORD __stdcall d5480_get_profile(WORD axis,double* option,double* Max_Vel,double* acc,double* dec);
DMC5480_API DWORD __stdcall d5480_get_s_profile(WORD axis,double* s_para);

DMC5480_API DWORD __stdcall d5480_reset_target_position(WORD axis,long dist);

//���ᶨ���˶�
DMC5480_API DWORD __stdcall d5480_pmove(WORD axis,long Dist,WORD posi_mode);

//���������˶�
DMC5480_API DWORD __stdcall d5480_vmove(WORD axis,WORD dir, double vel);

//���Բ岹
DMC5480_API DWORD __stdcall d5480_line2(WORD axis1,long Dist1,WORD axis2,long Dist2,WORD posi_mode);
DMC5480_API DWORD __stdcall d5480_line3(WORD *axis,long Dist1,long Dist2,long Dist3,WORD posi_mode);
DMC5480_API DWORD __stdcall d5480_line4(WORD cardno,long Dist1,long Dist2,long Dist3,long Dist4,WORD posi_mode);

//�����˶�
DMC5480_API DWORD __stdcall d5480_set_handwheel_inmode(WORD axis,WORD inmode, double multi);
DMC5480_API DWORD __stdcall d5480_handwheel_move(WORD axis);

//��ԭ��
DMC5480_API DWORD __stdcall d5480_config_home_mode(WORD axis,WORD home_dir, double vel, WORD mode, WORD EZ_count);
DMC5480_API DWORD __stdcall d5480_home_move(WORD axis);

//Բ���岹
DMC5480_API DWORD __stdcall d5480_arc_move(WORD *axis,long *target_pos,long *cen_pos, WORD arc_dir);
DMC5480_API DWORD __stdcall d5480_rel_arc_move(WORD *axis,long *rel_pos,long *rel_cen, WORD arc_dir);

//���úͶ�ȡλ�ñȽ��ź�
DMC5480_API DWORD __stdcall d5480_compare_config(WORD card, WORD enable, WORD axis,  WORD cmp_source);
DMC5480_API DWORD __stdcall d5480_compare_get_config(WORD card, WORD* enable, WORD* axis,  WORD* cmp_source);

DMC5480_API DWORD __stdcall d5480_compare_clear_points(WORD card);
DMC5480_API DWORD __stdcall d5480_compare_add_point(WORD card, long pos, WORD dir,  WORD action, long actpara);
DMC5480_API long __stdcall d5480_compare_get_current_point(WORD card);
DMC5480_API long __stdcall d5480_compare_get_points_runned(WORD card);
DMC5480_API long __stdcall d5480_compare_get_points_remained(WORD card);


//---------------------   ��������������  ----------------------//
DMC5480_API long __stdcall d5480_get_encoder(WORD axis);
DMC5480_API DWORD __stdcall d5480_set_encoder(WORD axis,long encoder_value);

DMC5480_API DWORD __stdcall d5480_config_EZ_PIN(WORD axis,WORD ez_logic, WORD ez_mode);
DMC5480_API DWORD __stdcall d5480_get_config_EZ_PIN(WORD axis,WORD* ez_logic, WORD* ez_mode);

DMC5480_API DWORD __stdcall d5480_config_LTC_PIN(WORD axis,WORD ltc_logic, WORD ltc_mode);

DMC5480_API DWORD __stdcall d5480_config_latch_mode(WORD cardno, WORD all_enable);

DMC5480_API long __stdcall d5480_get_latch_value(WORD axis);
DMC5480_API long __stdcall d5480_get_latch_flag(WORD cardno);
DMC5480_API DWORD __stdcall d5480_reset_latch_flag(WORD cardno);

DMC5480_API long __stdcall d5480_get_counter_flag(WORD cardno);
DMC5480_API DWORD __stdcall d5480_reset_counter_flag(WORD cardno);

DMC5480_API DWORD __stdcall d5480_reset_clear_flag(WORD cardno);

DMC5480_API DWORD __stdcall d5480_triger_chunnel(WORD cardno, WORD num);
DMC5480_API DWORD __stdcall d5480_set_speaker_logic(WORD cardno, WORD logic);

DMC5480_API DWORD __stdcall d5480_get_speaker_logic(WORD cardno, WORD* logic);
DMC5480_API DWORD __stdcall d5480_get_config_latch_mode(WORD cardno, WORD* all_enable);

//�����λ����
DMC5480_API DWORD __stdcall d5480_config_softlimit(WORD axis,WORD ON_OFF, WORD source_sel,WORD SL_action, long N_limit,long P_limit);
DMC5480_API DWORD __stdcall d5480_get_config_softlimit(WORD axis,WORD* ON_OFF, WORD* source_sel,WORD* SL_action,long* N_limit,long* P_limit);


//�����岹����
DMC5480_API DWORD  __stdcall d5480_conti_lines(WORD axisNum, WORD *piaxisList,
    long *pPosList, WORD posi_mode);

DMC5480_API DWORD  __stdcall d5480_conti_arc(WORD *axis, long *rel_pos, long *rel_cen, WORD arc_dir,  WORD posi_mode);

DMC5480_API DWORD  __stdcall d5480_conti_restrain_speed(WORD card, double v);

DMC5480_API  DWORD  __stdcall d5480_conti_change_speed_ratio(WORD card, double percent);
DMC5480_API  double    __stdcall d5480_conti_get_current_speed_ratio(WORD card);

DMC5480_API  DWORD  __stdcall d5480_conti_set_mode(WORD card, WORD conti_mode, double conti_vl, double conti_para, double filter);
DMC5480_API  DWORD  __stdcall d5480_conti_get_mode(WORD card, WORD* conti_mode, double* conti_vl, double* conti_para, double* filter);

DMC5480_API DWORD  __stdcall d5480_conti_open_list(WORD axisNum, WORD *piaxisList);
DMC5480_API DWORD  __stdcall d5480_conti_close_list(WORD card);
DMC5480_API DWORD  __stdcall d5480_conti_check_remain_space(WORD card);

DMC5480_API DWORD  __stdcall d5480_conti_decel_stop_list(WORD card);
DMC5480_API DWORD  __stdcall d5480_conti_sudden_stop_list(WORD card);
DMC5480_API DWORD  __stdcall d5480_conti_pause_list(WORD card);
DMC5480_API DWORD  __stdcall d5480_conti_start_list(WORD card);

DMC5480_API long __stdcall d5480_conti_read_current_mark(WORD card);
DMC5480_API DWORD  __stdcall d5480_conti_extern_lines(WORD axisNum, WORD *piaxisListw,
                                               long *pPosList, WORD posi_mode, long imark);
DMC5480_API DWORD  __stdcall d5480_conti_extern_arc(WORD *axis, long *rel_pos, long *rel_cen, WORD arc_dir,WORD posi_mode, long imark);
 
//PC�������
enum ERR_CODE_DMC
{
    ERR_NOERR = 0,          //�ɹ�      
    ERR_UNKNOWN = 1,
    ERR_PARAERR = 2,    
    
    ERR_TIMEOUT = 3,
    ERR_CONTROLLERBUSY = 4,
    ERR_CONNECT_TOOMANY = 5,    

    ERR_CONTILINE = 6,
    ERR_CANNOT_CONNECTETH = 8,
    ERR_HANDLEERR = 9, 
    ERR_SENDERR = 10, 
    ERR_FIRMWAREERR = 12, //�̼��ļ�����
    ERR_FIRMWAR_MISMATCH = 14, //�̼���ƥ��
    
    ERR_FIRMWARE_INVALID_PARA    = 20,  //�̼���������
    ERR_FIRMWARE_PARA_ERR    = 20,  //�̼���������2
    ERR_FIRMWARE_STATE_ERR    = 22, //�̼���ǰ״̬���������
    ERR_FIRMWARE_LIB_STATE_ERR    = 22, //�̼���ǰ״̬���������2
    ERR_FIRMWARE_CARD_NOT_SUPPORT    = 24,  //�̼���֧�ֵĹ��� ��������֧�ֵĹ���
    ERR_FIRMWARE_LIB_NOTSUPPORT    = 24,    //�̼���֧�ֵĹ���2
};

#ifdef __cplusplus
}
#endif

#endif 




















