#ifndef DSP2833x_USER_DEFINE_H
#define DSP2833x_USER_DEFINE_H

#ifdef __cplusplus
extern "C" {
#endif

#define F_RS_H GpioDataRegs.GPBSET.bit.GPIO44 = 1;
#define F_RS_L GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1;

#define RS485_TX1 GpioDataRegs.GPCSET.bit.GPIO70=1;
#define RS485_RX1 GpioDataRegs.GPCCLEAR.bit.GPIO70=1;

#define CS1H        GPIO_WritePin(94,1)
#define CS1L        GPIO_WritePin(94,0)
#define CLK1H       GPIO_WritePin(89,1)
#define CLK1L       GPIO_WritePin(89,0)
#define DI1H        GPIO_WritePin(90,1)
#define DI1L        GPIO_WritePin(90,0)

#define AUX_ON  GpioDataRegs.GPBSET.bit.GPIO48=1;
#define MAIN_ON GpioDataRegs.GPBSET.bit.GPIO47=1;

#define ALL_RELAY_OFF GpioDataRegs.GPBCLEAR.bit.GPIO48=1;GpioDataRegs.GPBCLEAR.bit.GPIO47=1;

#define FAN_OFF   GpioDataRegs.GPBCLEAR.bit.GPIO50=1;
#define FAN_ON    GpioDataRegs.GPBSET.bit.GPIO50=1;

#define EnablePWM    GpioDataRegs.GPCSET.bit.GPIO93=1;GpioDataRegs.GPESET.bit.GPIO133=1;//高有效
#define DisablePWM   GpioDataRegs.GPCCLEAR.bit.GPIO93=1;GpioDataRegs.GPECLEAR.bit.GPIO133=1;ALL_RELAY_OFF;

typedef struct {  
				  float  AS;
				  float  BS;
				  float  CS;
				  float  Valpha;		    // Output: stationary d-axis stator variable 
				  float  Vbeta;		    // Output: stationary q-axis stator variable
		 	 	} CLARKE;	            

typedef CLARKE *CLARKE_handle;

typedef struct {  
                  float  PAlpha;
				  float  PBeta;
                  float  PDs;     		// Input: stationary d-axis stator variable 
				  float  PQs;    	    // Input: stationary q-axis stator variable 
				  float  PSine;  
				  float  PCosine; 
				  char   sel;   
		 	 	} PARK;	            

typedef PARK *PARK_handle;

typedef struct {  float  Ref;   		// Input: Reference input 
				  float  Fdb;   		// Input: Feedback input 
				  float  Err;			// Variable: Error 
				  float  Kp;			// Parameter: Proportional gain
				  float  Up;			// Variable: Proportional output 
				  float  Ui;			// Variable: Integral output 	
				  float  OutPreSat;	    // Variable: Pre-saturated output
				  float  OutMax;		// Parameter: Maximum output 
				  float  OutMin;		// Parameter: Minimum output
				  float  Out;   		// Output: PID output 
				  float  Ki;			// Parameter: Integral gain
				  float  ErrMax;
				  float  ErrMin;
				 }PIDREG;	            

typedef PIDREG *PIDREG_handle;

typedef struct {  float  IPAlpha;  		// Output: stationary d-axis stator variable
				  float  IPBeta;		   // Output: stationary q-axis stator variable
				  float  IPDs;			// Input: rotating d-axis stator variable
				  float  IPQs;			// Input: rotating q-axis stator variable
				  float  IPSine;      
				  float  IPCosine;   
		 	 	} IPARK;	            

typedef IPARK *IPARK_handle;
            
typedef struct {
                float           V_pv;
                float           I_pv;
				float           V_ds;
				float           V_ds2;
				float           Power[16];
				float			MP_Vdc[16];
				float			OutVdc;
				float           Power_m[2];
				int             ex_status;
				int             nth;
				int             peak_lock;
				float           ori_cur;
				int				repeat;
				int				rep_num;
				float           Duty_max;
				char            trace;
				char            ov_cur_flg;
				char            ov_vol_flg;
			   }MPPT;
typedef MPPT * mppt_handle; 

typedef struct {
                int				V_pos;
				int				Angle_pos;
				int             F_sum;
				long            V_sum;
                long            V_grid[16];
				float           V_sin[16];
				int            	Err_V;
				int           	Err_norm;
				int             Err_Fre[16];
				int             Err_F_sum;
				int             Err_pos;
				int             Err_F; 
			   }GRID;
typedef GRID * GRID_handle;
typedef struct {
				float    wL;	  //角频率乘电感(pu),也就是电感的标幺
				float    Vfdbd;	  //网侧电压回馈Vd
				float    Ifdbd;	  //网侧电流回馈值Id
				float    Ifdbq;	  //网侧电流回馈值Iq
				float    Vd;      //控制模块输出：
				float    Vq;      //电压d q分量；对Valpha,Vbeta的控制实现软起动,在SVPWM模块实现
		        float    Vd_Pidout;
				float    Vq_Pidout;
			   }CURR_ADJ;
typedef CURR_ADJ * Curr_handle;

typedef struct  {
                 float  Alpha;          // Input: reference alpha-axis phase voltage
                 float  Beta;             // Input: reference beta-axis phase voltage
                 float  Da1;                  // Output: reference phase-a switching function
                 float  Da2;                  // Output: reference phase-b switching function
                 float  Db1;                  // Output: reference phase-c switching function
                 float  Db2;
                 float  Dc1;
                 float  Dc2;
                 Uint16 k;
                 Uint16 Pol;
                 Uint16 Sec;
                 Uint16 Reg;
                } SVPWM_Mul;
typedef SVPWM_Mul *SVPWM_Mul_handle;
     
typedef struct{
             unsigned long  cmd;
			 unsigned long  sign;
			 unsigned long lenth;
			   char   str[800];
               } TCPIPDATA;
typedef struct{
               unsigned long  cmdd;
			   unsigned long  signn;
			   unsigned long lenthh;
			   unsigned long runsign; 
			   unsigned long faultsign; 
               char strr[40];            
              } TCPIPDATA1;
typedef struct{
               unsigned long cmd1;
               unsigned long sign1;
               unsigned long lenth1;
               float         value1[27];
               } TCPIPDATA2;

typedef struct {
				float         Ua;        
				float         Ua_sum;
				float         Ua_sum_t;
				float         Ub;
				float         Ub_sum;
				float         Ub_sum_t;
				float         Uc;
				float         Uc_sum;
				float         Uc_sum_t;
				float         Udc;
				float         Udc_sum;
				float         Udc_sum_t;
				float         Pa;
				float         Pa_sum;
				float         Pa_sum_t;
				float         Pb;
				float         Pb_sum;
				float         Pb_sum_t;
                float         Pc;
				float         Pc_sum;
				float         Pc_sum_t;
				float         Ia0;
				float         Ia0_sum;
				float         Ia0_sum_t;
				float         Ib0;
				float         Ib0_sum;
				float         Ib0_sum_t;
				float         Ic0;
				float         Ic0_sum;
				float         Ic0_sum_t;
				float         Ia;
				float         Ia_sum;
				float         Ia_sum_t;
				float         Ib;
				float         Ib_sum;
				float         Ib_sum_t;
				float         Ic;
				float         Ic_sum;
				float         Ic_sum_t;
				float         Idc;
				float         Idc_sum;
				float         Idc_sum_t;
				float         P;
				float         P_sum;
				float         P_sum_t;
				float         Pq;
				float         Pq_sum;
				float         Pq_sum_t;
				float         PL;
				float         Pfdb;
				float         Tem;
				float         Tem_sum;
				float         Tem_sum_t;

				float         vdc_inverse;
				float         PF;

				unsigned int		      N;
				float         Count_Ratio;
				unsigned int           Count;
				
				int			  status;
				unsigned int			  Tx_int[30];
		 	   } Display;
typedef Display *Display_handle;

typedef struct {  
				int    uac_Min1;
				int    uac_Min2;
				int    uac_Min3;
				int    uac_Max1;
				int    uac_Max2;
				int    uac_Max3;

				int    Udc_Min1;
				int    Udc_Min2;
				int    Udc_Min3;
				int    Udc_Max1;
				int    Udc_Max2;
				int    Udc_Max3;

				int    iac_Min1;
				int    iac_Min2;
				int    iac_Min3;
				int    iac_Max1;
				int    iac_Max2;
				int    iac_Max3;

				int    Idc_Max1;
				int    Idc_Max2;
				int    Idc_Max3;

				int    Temp_max1;
				int    Temp_max2;
				int    Temp_max3;
		 	   } Extremum;	
typedef Extremum *Extre_handle;

typedef struct {
				Uint16          Year;
				int64		    Enrg_Y;
				Uint16          Month;
				int64		    Enrg_M;
				Uint16          Date;
				int64		    Enrg_D;
				int64         	Enrg;
	            int64         	Enrg_Pre;

				Uint16          Y_Update;
				Uint16          M_Update;
				Uint16          D_Update;
				Uint16          Mdfy_en;

				int32	        E_Total_Dis;
				int16         	E_date_Dis;
				int32         	E_Month_Dis;
				int32         	E_Year_Dis;

	            int64         	Enrg_Total;
	            int64         	Enrg_Total_Half;
	            float           Enrg_k;
               } Energy;
typedef Energy * Energy_handle;

typedef struct
{
	unsigned int Tx_Data1[64];
	unsigned int Rx_Data1[16];
	unsigned int Tx_Data2[16];
	unsigned int Rx_Data2[16];
	unsigned int Rx_Disp[64];
	unsigned int Tx_Num1;
	unsigned int Rx_Num1;
	unsigned int Tx_Num2;
	unsigned int Rx_Num2;
	unsigned int *p_Disp;
	unsigned int Tx_Cnt;
	unsigned int Rx_Cnt;
	unsigned int Rx_Flag;
	unsigned int Tx_Flag;
	unsigned int Modbus_add;
	unsigned int Time;
	unsigned int Tx_delay;
} Uart;
typedef Uart *Uart_handle;

typedef struct {
                    float32  Ipv;
                    float32  Vpv;
                    float32  DeltaPmin;
                    float32  MaxVolt;
                    float32  MinVolt;
                    float32  Stepsize;
                    float32  VmppOut;
                    float32  DeltaP;
                    float32  Power;
                    float32  Power_Prev;
                    int16 mppt_enable;
                    int16 mppt_first;
                    int16 Status;
                } MPPT_PNO_F;
typedef MPPT_PNO_F *mppt_pno_handle;

typedef struct
{
    float   Valpha[8];
    float   Freq;
    int    Valpha_buf[16];
    int    Valpha_sum;
    int    V_POS;
    int    Vz_POS;
    int    Sequence;
    int    Samples;
    int    SampleSum;
    int    Sample_n;
    unsigned int    Sample_Freq;
} THREE_ANALYZ;
typedef THREE_ANALYZ *Analyzer_handle;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2833x_USER_DEFINED_TYPE_H definition
