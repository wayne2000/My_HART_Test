#ifndef __HART_H
#define __HART_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <ADuCM360.h>

#include <WdtLib.h>
#include <ClkLib.h>
#include <DioLib.h>
#include <UrtLib.h>
#include <IntLib.h>
#include <GptLib.h>

typedef uint8_t			u8;
typedef uint16_t		u16;
typedef uint32_t		u32;

#ifndef TRUE
#define TRUE			1
#endif
#ifndef FALSE
#define FALSE			0
#endif

#define DEBUG

#define PREAMBLE             0xFF
#define PREAMBLE_DEFAULT_NUM 5
#define PREAMBLE_MAX_NUM     20

#define TMR_CNT     3

#define GAP_TIMER   0    
#define SLAVE_TIMER 1
#define BT_TIMER    2

#define HART_STO       260 /* unit:ms, sto = 256.7ms */
#define HART_PRI_RT1   305 /* unit:ms,  = 302.5ms */
#define HART_SEC_RT1   380 /* unit:ms,  = 375.8ms */
#define HART_RT2       75  /* unit:ms,  = 73.3ms */
#define HART_GAPT      20  /* unit:ms,  = 9.2ms */

#define LONG_ADDR_SIZE  5
#define SHORT_ADDR_SIZE 1

#define LONG_FRAME     0x80
#define SHORT_FRAME    0x00

/* short frame information offset address */
#define HART_SHORTF_DELIMITER_OFF  0
#define HART_SHORTF_ADDR_OFF       1
#define HART_SHORTF_CMD_OFF        2
#define HART_SHORTF_LEN_OFF        3
#define HART_SHORTF_REQDATA_OFF    4
#define HART_SHORTF_RSPCODE1_OFF   4
#define HART_SHORTF_RSPCODE2_OFF   5
#define HART_SHORTF_RSPDATA_OFF    6

/* long frame information offset address */
#define HART_LONGF_DELIMITER_OFF   0
#define HART_LONGF_ADDR_OFF        1
#define HART_LONGF_CMD_OFF         6
#define HART_LONGF_LEN_OFF         7
#define HART_LONGF_REQDATA_OFF     8
#define HART_LONGF_RSPCODE1_OFF    8
#define HART_LONGF_RSPCODE2_OFF    9
#define HART_LONGF_RSPDATA_OFF     10

/* slave/burst-mode  master */
#define BURST_MODE        1
#define SALVE_MODE        0

enum{
	DISABLE,
	ENABLE
};

enum alarm{
	HIGH_ALARM = 0,
	LOW_ALARM = 1,
	NONE_ALARM = 251,
};

enum transfer_func{
	LINEAR = 0,
	SQUARE_ROOT,
	NONE_FUNC = 251,
};

enum protect{
	NO_PROTECT,
	YES_PROTECT,
};

enum analog_channel{
	CHANNEL_FLAG = 0x01,
};

enum {
	DEVICE_VARIABLE_NOT_CLASSIFICATION = 0,
	PERCENT_UNIT = 57, // %
	CURRENT_UNIT = 39, // mA
	TORQUE =110 ,  //table 21 TORQUE(110)
	//SV_CLASS,
	//TV_CLASS,
	//QV_CLASS,
	/* DV code */
	BATTERY_LIFE = 243,  //table 34
	PERCENT_RANGE = 244,
	LOOP_CURRENT,
	PV_CODE,
	//SV_CODE,
	//TV_CODE,
	//QV_CODE,
};

enum{
	SECONDARY_MASTER,
    PRIMARY_MASTER,
};

enum{
	UNDEFINED_FLAG_ASSINMENT = 0x00,
	MULTI_SENSOR_FIELD_DEVICE = 0x01,
	EEPROM_CONTROL = 0x02,
	PROTOCOL_BRIDGE_DEVICE = 0x04,
	IEEE802_15_4_DSSS = 0x08,
	C8PSK_CAPABLE_FIELD_DEVICE = 0x40,
	C8PSK_IN_MULTI_DROP_ONLY = 0x80,
};

enum extended_device_status{
	UNDEFINED_EXPANDED_DEVICE_STATUS = 0x00,
	MAINTANANCE_REQUIRED         = 0x01,
	DEVICE_VARIABLE_ALERT        = 0x02,
	CRITICAL_POWER_FAILURE       = 0x04,
	FAILIRE_DEVICE_STATUS		= 0x10,
	FUNCTION_CHECK				= 0x20,	
};

enum standardized_status_0{
	SIMULATION_ACTIVE             = 0x01,
	NON_VOLATILE_MEMORY_DEFECT    = 0x02,
	VOLATILE_MEMORY_DEFECT        = 0x04,
	WATCHDOG_RESET_EXECUTE        = 0x08,
	VOTAGE_OUT_OF_RANGE           = 0x10,
	ENVIRONMENTAL_OUT_OF_RANGE    = 0x20,
	ELECTRONIC_DEFECT             = 0x40,
};

enum device_profile_codes{
	PROCESS_AUTOMATION_DEVICE = 1,
	DISCRETE_DEVICE = 2,
	HYBRID_DEVICE = 3,
	IO_SYSTEM = 4,
	DISCRETE_ADAPTER = 14,
	WIRELESS_PROCESS_AUTOMATION_DEVICE = 129,
	WIRELESS_DISCRETE_DEVICE = 130,
	WIRELESS_HYBRIDE_DEVICE = 131,
	WIRELESS_GATEWAY = 132,
	WIRELESS_ACCESS_POINT = 140,
	WIRELESS_PROCESS_ADAPTER = 141,
	WIRELESS_DISCRETE_ADAPTER = 142,
	WIRELESS_ENABLE_HANDHELD = 144,
};

enum engineering_unit_codes{
	DEGREES_CELSIUS = 32,
	DEGREES_FAHRENHEIT = 33,
	DEGREES_MILLVOLT = 36,
	DEGREES_OHM = 37,
	DEGREES_MILLIAMPERE = 39,
	DEGREES_INCH = 47,
	DEGREES_MILLIMETER = 49,
	DEGREES_MINUTE = 50,
	DEGREES_SECOND = 51,
	DEGREES_HOUR = 52,
	DEGREES_DAY = 53,
	DEGREES_PERCENT = 57,
	DEGREES_VOLT = 58,
	DEGREES_NOTUSED = 250,
	DEGREES_NONE = 251,
	DEGREES_UNKNOWN = 252,
	DEGREES_SPECIAL = 253,
};

enum device_variable_status{
	PDQ_GOOD = 0xC0,
	PDQ_POOR_ACCURACY = 0x40,
	PDQ_MANUAL_FIXED = 0x80,
	PDQ_BAD = 0x00,
	LS_CONSTANT = 0x30,
	LS_LOW_LIMITED = 0x10,
	LS_HIGH_LIMITED = 0x20,
	LS_NOT_LIMITED = 0x00,
	MORE_DVSA = 0x08,
};

enum device_variable_family_codes{
	DFC_TEMPERATURE = 4,
	DFC_PRESSURE,
	DFC_VALVE_ACTUATOR,
	DFC_PID,
	DFC_PH,
	DFC_CONDUCTIVITIY,
	DFC_TOTALIZER,
	DFC_LEVEL,
	DFC_VORTEX_FLOW,
	DFC_MAG_FLOW,
	DFC_CORIOLIS_FLOW,
	DFC_NOT_USED= 250,
};

/* STX : a master to slave message */
/* ACK : a slave to master message */
/* BACK : a slave message transmited to a master without an STX*/
/* the type of message received */
typedef enum{
	RCV_ERR  = 0xff,
	RCV_COMM_ERR = 0xee,
	RCV_STX  = 0x02,
	RCV_ACK  = 0x06,
	RCV_BACK = 0x01,
}Rcv_Msg_Type;

/* the type of message sended */
typedef enum{
	XMT_ERR  = 0xff,
	XMT_COMM_ERR = 0xee,
	XMT_STX  = 0x02,                       
	XMT_ACK  = 0x06,                       
	XMT_BACK = 0x01,                      
}Xmt_Msg_Type;

typedef enum{
    BELL_202_CURRENT = 0,
    BELL_202_VOLTAGE = 1,
    RS_485 = 2,
    RS_232 = 3,
    WIRELESS = 4,
    SPECIAL = 6
}PhysicalSignalDefinition;

// receive state machine
typedef enum{
	RCV_WAIT_IDLE,
	RCV_WAIT_START,
	RCV_READ,
	RCV_DONE,
}RSM_State;

// transmit state machine
typedef enum{
	XMT_INIT,
	XMT_WRITE,
	XMT_DONE,
}TSM_State;

// HART Status
typedef enum{
	HART_WAIT,
	HART_PROCESS,
}HART_State;

typedef struct{
	u16 cnt;
	u8 flg;
}Soft_Timer;

typedef struct {
	u8 device_type[2];
	u8 unique_device_id[3];
}Long_Addr_Type;

typedef struct {
	u8 preamble_num;
	u8 delimiter;
	u8 address_size;
	u8 cmd;
	u8 byte_count;
	u8 data_buf[100];
	u8 check_byte;
}Tx_Frame_Type;

typedef struct {
	u8 preamble_num;
	u8 delimiter;
	u8 address_size;
	u8 cmd;
	u8 byte_count;
	u8 data_buf[50];
	u8 check_byte;
}Rx_Frame_Type;

void  Set_Pv(float pv);
float Get_Pv(void);
void  Set_Sv(float sv);
float Get_Sv(void);
void  Set_Tv(float tv) ;
float Get_Tv(void);
void  Set_Qv(float qv);
float Get_Qv(void);
void Set_Pv_Unit(u8 pv_unit);
u8 Get_Pv_Unit(void);
void Set_Sv_Unit(unsigned char sv_unit);
u8 Get_Sv_Unit(void);
void Set_Tv_Unit(unsigned char tv_unit);
u8 Get_Tv_Unit(void);
void Set_Qv_Unit(unsigned char qv_unit);
u8 Get_Qv_Unit(void);
void Set_Pv_Code(u8 pv_code);
u8 Get_Pv_Code(void);
void Set_Sv_Code(u8 sv_code);
u8 Get_Sv_Code(void);
void Set_Tv_Code(u8 tv_code);
u8 Get_Tv_Code(void);
void Set_Qv_Code(u8 qv_code);
u8 Get_Qv_Code(void);
void Set_Pv_Status(u8 pv_status);
u8 Get_Pv_Status(void);
void  Set_Loop_Current(float current);
float Get_Loop_Current(void);
void  Set_Percent_Of_Range(float percent_of_range);
float Get_Percent_Of_Range(void);
void Set_Burst_Mode(u8 bt_code);
u8 Get_Burst_Mode(void);
void Set_Response_Preamble_Num(u8 rsp_preamble_num);
u8 Get_Response_Preamble_Num(void);
void Set_Ul_Range_Unit(u8 ul_range_unit);
u8 Get_Ul_Range_Unit(void);
void Set_Polling_Addr(u8 polling_addr);
u8 Get_Polling_Addr(void);
void Set_Loop_Current_Mode(u8 current_mode);
u8 Get_Loop_Current_Mode(void);
void Set_Extended_Device_Status(u8 status);
u8 Get_Extended_Device_Status(void);
void Set_Std_Status_0(u8 status_0);
u8 Get_Std_Status_0(void);
void Set_Std_Status_1(u8 status_1);
u8 Get_Std_Status_1(void);
void Set_Std_Status_2(u8 status_2);
u8 Get_Std_Status_2(void);
void Set_Std_Status_3(u8 status_3);
u8 Get_Std_Status_3(void);
void Set_Analog_Channel_Saturation(u8 Acs);
u8 Get_Analog_Channel_Saturation(void);
void Set_Analog_Channel_Fixed(u8 Acf);
u8 Get_Analog_Channel_Fixed(void);
u8 Get_Extended_Device_Status(void);
void Set_Pv_Zero(float pv_zero);
float Get_Pv_Zero(void);
void Set_Message(u8 *msg);
u8 *Get_Message(void);
void Set_Tag(u8 *tag);
u8 *Get_Tag(void);
void Set_Descriptor(u8 *dscp);
u8 *Get_Descriptor(void);
void Set_Date(u8 *date);
u8 *Get_Date(void);
void Set_LongTag(u8 *longtag);
u8 *Get_LongTag(void);
void Set_Transducer_Serial_Num(u8 *tsn);
u8 *Get_Transducer_Serial_Num(void);
void Set_Transducer_Upper(float tsd_upper);
float Get_Transducer_Upper(void);
void Set_Transducer_Lower(float tsd_lower);
float Get_Transducer_Lower(void);
void Set_Pv_Min_Span(float min_span);
float Get_Pv_Min_Span(void);
void Set_Pv_Upper_Range(float upper_range);
float Get_Pv_Upper_Range(void);
void Set_Pv_Lower_Range(float lower_range);
float Get_Pv_Lower_Range(void);
void Set_Pv_Damping_Time(float damping_time);
float Get_Pv_Damping_Time(void);
void Set_Alarm_Sw(enum alarm alarm);
enum alarm Get_Alarm_Sw(void);
void Set_Transfer_Func(enum transfer_func tsf_func);
enum transfer_func Get_Transfer_Func(void);
void Set_Protect(enum protect protect_status);
enum protect Get_Protect(void);
void Set_Analog_Channel(enum analog_channel analog_chl);
enum analog_channel Get_Analog_Channel(void);
void Set_Final_Assembly_Num(u8 *fan);
u8 *Get_Final_Assembly_Num(void);
void Set_Config_Change_Flag(u8 cfg_change_flag);
u8 Get_Config_Change_Flag(void);
void Set_Config_Change_Counter(u16 cfg_change_flag);
u16 Get_Config_Change_Counter(void);
void Set_Fixed_Current(float fixed_current);
float Get_Fixed_Current(void);
void Set_Act_Zero_Current(float act_zero_curr);
float Get_Act_Zero_Current(void);
void Set_Act_Gain_Current(float act_gain_current);
float Get_Act_Gain_Current(void);
void Set_Device_Specific_Status(u8 *dss);
u8 *Get_Device_Specific_Status(void);
void Set_Device_Operating_Mode(u8 mode);
u8 Get_Device_Operating_Mode(void) ;
u8 Get_Host_Type(void);
void Set_CORR_Value(float correct_value) ;
float Get_CORR_Value(void);
void Set_CORR_Unit(u8 correct_unit);
u8 Get_CORR_Unit(void);
void Set_CORR_Code(u8 correct_code);
u8 Get_CORR_Code(void);
void Set_CORR_Status(u8 correct_status) ;
u8 Get_CORR_Status(void) ;
void Set_UserSet_20mA_Value(float userset_20ma_value);
float Get_UserSet_20mA_Value(void) ;
void Set_UserSet_20mA_Unit(u8 userset_20ma_unit) ;
u8 Get_UserSet_20mA_Unit(void) ;
void Set_UserSet_20mA_Code(u8 userset_20ma_code) ;
u8 Get_UserSet_20mA_Code(void) ;
void Set_UserSet_20mA_Status(u8 userset_20ma_status);
u8 Get_UserSet_20mA_Status(void) ;
void Set_UserSet_4mA_Value(float userset_4ma_value) ;
float Get_UserSet_4mA_Value(void);
void Set_UserSet_4mA_Unit(u8 userset_4ma_unit);
u8 Get_UserSet_4mA_Unit(void);
void Set_UserSet_4mA_Code(u8 userset_4ma_code);
u8 Get_UserSet_4mA_Code(void) ;
void Set_UserSet_4mA_Status(u8 userset_4ma_status);
u8 Get_UserSet_4mA_Status(void) ;
void Set_CurrentDir_Value(float currentdir_value) ;
float Get_CurrentDir_Value(void) ;
void Set_CurrentDir_Unit(u8 currentdir_unit);
u8 Get_CurrentDir_Unit(void);
void Set_CurrentDir_Code(u8 currentdir_code);
u8 Get_CurrentDir_Code(void);
void Set_CurrentDir_Status(u8 currentdir_status);
u8 Get_CurrentDir_Status(void);
void Set_Density_Value(float density_value);
float Get_Density_Value(void);
void Set_Density_Unit(u8 density_unit);
u8 Get_Density_Unit(void) ;
void Set_Density_Code(u8 density_code) ;
u8 Get_Density_Code(void);
void Set_Density_Status(u8 density_status);
u8 Get_Density_Status(void) ;
void Set_Contrast_Value(float contrast_value) ;
float Get_Contrast_Value(void) ;
void Set_Contrast_Unit(u8 contrast_unit) ;
u8 Get_Contrast_Unit(void);
void Set_Contrast_Code(u8 contrast_code);
u8 Get_Contrast_Code(void);
void Set_Contrast_Status(u8 contrast_status);
u8 Get_Contrast_Status(void);

void Init_Param(void);
void Soft_Timer_Init(void);
void TIMER0_Init(void);
void HART_Init(void);
void HART_polling(void);
static void HART_Wait(void);
static void HART_Process(void);
u16 Cmd_Function(u8 cmd, u8 *data);
void Frame_Cmd_Data(void);
static u8 Is_Addr_Match(void);
static u8 Longitudinal_Parity(u8 *data, u16 cnt);

void UART_Init();
void UART_Enable(u8 rx_enable, u8 tx_enable);
void HART_Tx_Msg(void);
void HART_Rx_Msg(void);

void Send_Byte(const u8 ch);
void Send_Msg(const u8 *str);

void Set_Rcv_Frame_Count(void);
void Enter_Critical_Section(void);
void Exit_Critical_Section(void);

u8 Packed_ASCII(const u8* Src, u16 SrcLen, u8* Dst, u16 DstLen);
u8 Unpcked_ASCII(const u8* Src,u16 SrcLen,u8 *Dst,u16 DstLen);


static void Soft_Timer_Dec(Soft_Timer *tmr);
void Set_Delay_Time(u8 id,u16 cnt);
u8 Is_Timeout_Id(u8 id);

void Set_ID(u8 *data);
static void Config_Change(u16 CmdCode);
static float Data_To_Float(u8 *tmp);
static void Float_To_Data(u8 *data,float *tmp);
u8 *Get_Rx_Data_Pointer(void);
void Set_Data_Link(void);
void Set_Response_Code(u8 *data);

void C0_RdUniqueId(u8 *data);
void C1_RdPV(u8 *data);
void C2_RdLoopCurrPerOfRange(u8 *data);
void C3_RdDVLoopCurr(u8 *data);
void C6_WrPollingAddr(u8 *data);
void C7_RdLoopConfiguration(u8 *data);
void C8_RdDVClass(u8 *data);
void C9_RdStatusDV(u8 *data);
void C11_RdUniqueIDWithTag(u8 *data);
void C12_RdMessage(u8 *data);
void C13_RdTagDescriptorDate(u8 *data);
void C14_RdPVTransducerInfo(u8 *data);
void C15_RdDeviceInfo(u8 *data);
void C16_RdFinalAssemblyNum(u8 *data);
void C17_WrMessage(u8 *data);
void C18_WrTagDescriptorDate(u8 *data);
void C19_WrFinalAssemblyNum(u8 *data);
void C20_RdLongTag(u8 *data);
void C21_RdUniqueIDWithLongTag(u8 *data);
void C22_WrLongTag(u8 *data);
void C33_RdDeviceVariable(u8 *data);
void C34_WrPVDamping(u8 *data);
void C35_WrPVRange(u8 *data);
void C36_SetPVUpperRange(u8 *data);
void C37_SetPVLowerRange(u8 *data);
void C38_ResetCfgChangeFlag(u8 *data);
void C40_EnterOrExitFixedCurrent(u8 *data);
void C41_PerformSelfTest(u8 *data);
void C42_PerformDeviceReset(u8 *data);
void C43_PVZero(u8 *data);
void C44_WrPVUnit(u8 *data);
void C45_TrimLoopCurrentZero(u8 *data);
void C46_TrimLoopCurrentGain(u8 *data);
void C47_WrPVTransferFunction(u8 *data);
void C48_RdAdditionalDeviceStatus(u8 *data);
void C49_WrPVTransducerSerialNum(u8 *data);
void C50_RdDVAssignments(u8 *data);
void C51_WrDVAssignments(u8 *data);
void C59_WrNumOfResposePreambles(u8 *data);
void C108_WrBurstModeCmdNum(u8 *data);
void C109_BurstModeControl(u8 *data);
void C200_WrTest(u8 *data);

#endif
