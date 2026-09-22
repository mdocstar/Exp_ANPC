#include "F28x_Project.h"     // Device Headerfile and Examples Include File
#include "F2837xD_Ipc_drivers.h"
#include <math.h>

#define CLARKE_DEFAULTS { 0.0, \
                          0.0, \
                          0.0, \
                          0.0, \
                          0.0, \
              			}

#define PARK_DEFAULTS {   0.0, \
                          0.0, \
                          0.0, \
                          0.0, \
                          0.0, \
                          0.0, \
                          0,   \
					  }

#define PIDIQ_DEFAULTS   { 	0,\
/*  Fdb   */            	0,\
/*  Err   */             	0,\
/*  Kp   */	               	2,\
/*  Up   */                 0,\
/*  Ui   */	               	0,\
/*  OutPreSat   */        	0,\
/*  OutMax   */             600,\
/*  OutMin   */        		-600,\
/*  Out   */                0,\
/*  Ki  */                 	0.00005,\
                            20.0,\
                            -20.0,\
						 }

#define PIDVDC_DEFAULTS   { 0,\
/*  Fdb   */            	0,\
/*  Err   */             	0,\
/*  Kp   */	               	0.1,\
/*  Up   */                 0,\
/*  Ui   */	               	0,\
/*  OutPreSat   */        	0,\
/*  OutMax   */             3,\
/*  OutMin   */        		-5,\
/*  Out   */                0,\
/*  Ki  */                 	0.0002,\
                            20.0,\
                            -20.0,\
						  }

#define IPARK_DEFAULTS {  0.0, \
                          0.0, \
                          0.0, \
                          0.0, \
                          0.0, \
						  0.0, \
              		   }

#define CURR_DEFAULTS {	1.57,\
						0.0,  \
						0.0,  \
						0.0,  \
						0.0,  \
						0.0,  \
						0.0,  \
						0.0,  \
					   }


#define GRID_DEFAULTS  {\
/*V_pos*/                    0,\
/*Angle_pos*/				 0,\
/*F_sum*/					 0,\
/*V_sum*/					 0,\
/*V_grid[16]*/				 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
/*V_sin*/                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
/*Err_V*/					 0,\
/*Err_norm*/				 15,\
/*Err_Fre[16]*/              {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
/*Err_F_sum*/				 0,\
/*Err_pos*/		    		 0,\
/*Err_F*/		    		 0,\
					      }
#define SVPWM_Mul_DEFAULTS   {\
/*Alpha*/                     0.4,\
/*Beta*/                      0.4,\
/*Ta1*/                       0,\
/*Ta2*/                       1,\
/*Tb1*/                       0,\
/*Tb2*/                       1,\
/*Tc1*/                       0,\
/*Tc2*/                       1,\
/*k*/                         0,\
/*Pol*/                       1,\
/*Sec*/                       0,\
/*Reg*/                       0,\
                             }

#define Dis_Para_DEFAULTS {\
						   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,\
						   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,\
						   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,\
						   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,0,\
						   0.004,1, 	 1199, 0.0008333333,0,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},\
                          }

#define Extre_DEFAULTS    {\
/*VAC Min & Max*/          -480,  60,  150,    260,   280, 480,\
/*VDC Min & Max*/          200,  240,  250,    755,   780,  820,\
/*iAC Min & Max*/          -80,  -30,  -20,    10,    30,  80,\
/*IDC & TEMP  Max*/        -5,   500,  -0,    65,    75,   85,\
                          }

#define Energy_DEFAULTS	   {\
							0,\
							0,\
							0,\
							0,\
							0,\
							0,\
							0,\
							0,\
							0,\
							0,\
							0,\
							0,\
							0,\
							0,\
							0,\
							0,\
	                        3599971200230398157,\
	                        -1700000000000000000,\
	                        2.7778e-10f,\
                           }

#define Uart1_DEFAULTS  {\
/*Tx_Data1*/             {0x01,0x04,0,0,0,0,0,0},\
/*Rx_Data1*/             {0,0,0,0,0,0,0,0},\
/*Tx_Data2*/             {0x01,0x00,0,0,0,0,0,0},\
/*Rx_Data2*/             {0,0,0,0,0,0,0,0},\
/*Rx_Disp*/              {0,0,0,0,0,0,0,0},\
/*Tx_Num1*/               8,\
/*Rx_Num1*/               32,\
/*Tx_Num2*/               8,\
/*Rx_Num2*/               8,\
                          NULL,\
/*Tx_Cnt*/                0,\
/*Rx_Cnt*/                0,\
/*Rx_Flag*/               0,\
/*Tx_Flag*/               0,\
                          1,\
                          0,\
                          0,\
                        }

/*-----------------------------------------------------------------------------
the end
-----------------------------------------------------------------------------*/
CLARKE         V_clarke    = CLARKE_DEFAULTS;
CLARKE         I_clarke    = CLARKE_DEFAULTS;
PARK           V_park      = PARK_DEFAULTS;
PARK           I_park      = PARK_DEFAULTS;
IPARK          I_ipark     = IPARK_DEFAULTS;
PIDREG         Id_pidreg   = PIDIQ_DEFAULTS;
PIDREG         Iq_pidreg   = PIDIQ_DEFAULTS;
PIDREG         V_pidreg    = PIDVDC_DEFAULTS;
CURR_ADJ       V_CURR_ADJ  = CURR_DEFAULTS;

GRID           grid_paras  = GRID_DEFAULTS;
SVPWM_Mul      Svgen_Mul   = SVPWM_Mul_DEFAULTS;

Display		   Dis_Para		= Dis_Para_DEFAULTS;
Extremum	   Extre		= Extre_DEFAULTS;
Energy		   ENRG_Data	= Energy_DEFAULTS;

Uart            Uart1       = Uart1_DEFAULTS;

THREE_ANALYZ  ThreeAnalyz ={{0},0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},0,0,0,0,0,0,0,20000};
/*-----------------------------------------------------------------------------

-----------------------------------------------------------------------------*/
//#define _FLASH 1
Uint16  ReadAd(void);

void  clarke_calc(CLARKE_handle v);
void  park_calc(PARK_handle v);
void  CurrControl(Curr_handle v);
void  ipark_calc(IPARK_handle v);

void  CtrlProcess (void);
void  pid_reg_calc(PIDREG_handle v);
void  SVPWM_Mul_Calc(SVPWM_Mul_handle v);

int Grid_Check(GRID_handle grid_para,PARK_handle V_p);
void Three_phase_Analyzer(CLARKE_handle Vc,Display_handle Dis,Analyzer_handle Ay);

interrupt void EPwm1ISR(void);

void GetCrcCode(Uint16 len,Uint16 * str);
void int_char(Uint16 len, Uint16 * Dest,Uint16 * Source);
Uint16 ModbusCRCHi[];
Uint16 ModbusCRCLo[];

void Paramcalc1(void);
void Paramcalc2(void);

void Reset_status(void);

void Scib_Check(void);
void Scib_Data_Process(void);
void Scib_Data_Tx(void);
void RESET_SCIB(void);
void RESET_SCIC(void);

void Protect(unsigned int s);
void fault_action(void);
void fault_reset(void);

void I2C_Operation(void);
void WR_Flash(Uint16* x);

void ENRG_Compute(Energy_handle E);

/*-----------------------------------------------------------------------------
the end
-----------------------------------------------------------------------------*/
//ABC三相电感电流采集值，直流电流采集值
volatile float Ia=0,Ib=0,Ic=0,Idc=0;
//ABC三相电压值，Udc直流电压平均值
volatile float Ua=0,Ub=0,Uc=0,Uab=0,Ubc=0,Udc=0;
//直流上端与中点电压采样，中点与直流下端电压采样
volatile float Udcp=0,Udcn=0;
//直流电压参考值
volatile float Dc_BusVolt_Ref=600;
volatile float Vdcs[4]={0,0,0,0};
volatile Uint16 Udc_count=0;

//温度计算各参数，B=3750,T25=298.15,Vt为上拉电压，Rt为上端分压电阻
float R25_N=0.1,T25_N=0.003354,T0=273.15,Vt=12.05,B5025_N=0.000266666,Rt=100;
//NTC10K热敏电阻25℃下标准阻值
volatile float R1=10;
volatile float Vtemp;

//电流、电压采集补偿值
float offset1=60,offset2=60,offset3=60,offset4=75,offset5=75;

//标志位相关
volatile int flg1=0,flg2=0,Fault_I=0,Fault_U=0;
volatile int Fault2=0x1000,Fault1=0x1000,WR_En=0;

volatile Uint32 rs_time = 0;

//变压器相关
float Vpre_rate=1.01;

volatile float Plimit_P=10,Plimit_N=-10,P_set=0;

int P_rated,p_cal_cnt=0;

void main(void)
{
	Uint16 i;float temp;

	InitSysCtrl();      //系统初始化

	#ifdef _STANDALONE
	#ifdef _FLASH
	// Send boot command to allow the CPU2 application to begin execution
	IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH);
	#else
	// Send boot command to allow the CPU2 application to begin execution
	IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_RAM);
	#endif
	#endif

//	// Call Flash Initialization to setup flash waitstates
//	// This function must reside in RAM
	#ifdef _FLASH
	   InitFlash();
	#endif

	DINT;                   //禁止CPU中断

	InitPieCtrl();          //初始化PIE模块的寄存器到默认状态：禁止所有PIE中断，中断标志位都为0

	IER = 0x0000;           //禁止CPU中断并清除CPU中断标志位
	IFR = 0x0000;

	InitPieVectTable();     //初始化中断向量表

	//GPIO初始化
	GPIO_Setup();
	InitEPwmGpio();

	InitScibGpio();
	InitScicGpio();

	//外设初始化
    InitAdc();
    InitSci();
    InitEPwm();

	EALLOW;                 //使能对EALLOW保护寄存器的写操作
	PieVectTable.EPWM1_INT = &EPwm1ISR;     //为中断向量列表中的特定向量写入中断服务函数的地址
	EDIS;


	IER |= M_INT3;          //使能第三组中断INT3
	PieCtrlRegs.PIEIER3.bit.INTx1 = 1;	//使能PWM1中断

	EINT;       //使能全局中断
	ERTM;       //使能全局实时中断RBGM

	//部分变量初始化
	P_rated		    = 10;            //变流器额定功率，单位kW
	P_set			= P_rated * 5; //变流器运行功率设定值,默认5kW

	//PID参数初始化
	V_pidreg.Kp    = 1.0;
	V_pidreg.Ki    = 0.0004;
	V_pidreg.OutMax= Plimit_P;
	V_pidreg.OutMin= Plimit_N;
	Id_pidreg.Kp    = 5.0;
	Id_pidreg.Ki    = 0.00006;
	Id_pidreg.OutMax= 600.0;
	Id_pidreg.OutMin= -600.0;
	Iq_pidreg.Kp    = 5.0;
	Iq_pidreg.Ki    = 0.00006;
	Iq_pidreg.OutMax= 600.0;
	Iq_pidreg.OutMin= -600.0;


	//电流采样调零，在中断里进行采样处理求得0电流时的偏置
	i=0;
	while(i<20)
	{
		while(!Dis_Para.status);
		Dis_Para.status=0;
		i++;
	}
	Dis_Para.status|=0x04;              //调零结束

	temp=Dis_Para.Ia0_sum_t * Dis_Para.Count_Ratio;
	offset1=offset1-temp;               //A相逆变电流补偿值

	temp=Dis_Para.Ic0_sum_t * Dis_Para.Count_Ratio;
	offset2=offset2-temp;               //C相逆变电流补偿值

	temp=Dis_Para.Idc_sum_t * Dis_Para.Count_Ratio;
	offset3=offset3+temp;               //直流电流补偿值

	while(1)
	{
		temp=fabs(Dis_Para.P);          //运行功率绝对值

        if((Dis_Para.Tem > 65)||(temp>5000))//屏幕显示温度大于65℃或者功率超过5kW，开启风扇
            FAN_ON
        else if(Dis_Para.Tem < 55)      //屏幕显示温度小于55℃，关闭风扇
            FAN_OFF

		if(Dis_Para.status & 0x01)      //在PWM中断内完成一次参数计算
		{
            Paramcalc2();               //屏幕显示参数计算
            Protect(4);                 //平均值保护处理
            Dis_Para.status &=0xfffe;   //status赋值为0
		}

		if(Fault1)	Fault2=Fault1;      //Fault1不为0表示有故障，更新触摸屏故障状态，Fault2用于触摸屏显示，Fault1用于DSP

		Fault_I = EPwm1Regs.TZOSTFLG.bit.OST1;  //为1表示有ONE-SHORT事件产生
		if(Fault_I)
		{
			Fault1 |= 0x04;             //过流标志位置1
			fault_action();             //失能3245芯片，关闭主继电器、辅继电器，复位标志位
			Fault2=Fault1;              //fault1用于DSP处理，fault2用于组态屏显示
		}
		else if(Fault1 & 0x04)          //上一周期发生过流故障，本周期没有过流故障，则清除过流故障
		{
			Fault1 &= 0xfffb;           //清除过流标志位
		}

        Fault_U = EPwm1Regs.TZOSTFLG.bit.OST2;  //为1表示有ONE-SHORT事件产生
        if(Fault_U)
        {
            Fault1|=0x400;              //过压标志位置1
            fault_action();             //失能3245芯片，关闭主继电器、辅继电器，复位标志位
        }

        if(Uart1.Tx_delay > 100)        //485应答10mS延时
        {
            Uart1.Tx_delay=0;
            Scib_Data_Process();
        }

//		ENRG_Compute(&ENRG_Data);//发电量计算
//
//		WR_Flash((Uint16* )(&ENRG_Data.Enrg));//发电量保存

	}
}

interrupt void EPwm1ISR(void)
{
    int temp;

	PieCtrlRegs.PIEACK.all = 0x0004;        //清除中断组3的ACK位，以便再次响应

    if((ScibRegs.SCICTL2.bit.TXEMPTY)&&(!Uart1.Tx_Flag))    //485方向控制 发送完成转为接收
        RS485_RX1;
	Scib_Check();       //接收一个字节
	ReadAd();           //读取AD结果寄存器的值
	Protect(1);         //瞬时值保护

	CtrlProcess();      //控制参数计算 或 用于显示数据

	if(((!Fault1)&&(!flg2)))    //无故障且置开机标志位，并网启动
	{
		rs_time++;
		if(rs_time==40000)      //2s
		{
			AUX_ON;	            //辅助接触器开
		}
		if(rs_time==60000)      //3s
		{
			MAIN_ON;            //主接触器开
			Fault2=Fault1;
		}
		if(rs_time==70000)
			Reset_status();
	}
	else rs_time=0;

	if(flg2 & 0x01)
	{
	    SVPWM_Mul_Calc(&Svgen_Mul); //SVPWM计算及更新寄存器
		LoadPWM;                    //加载PWM

		if(flg1==0x02)
		{
			EnablePWM;              //使能PWM
			flg1=8;
			WR_En=3;
		}
		if(flg1==0x01)
		    flg1=2;
	}

    Paramcalc1();                   //参数计算函数

    Three_phase_Analyzer(&V_clarke,&Dis_Para,&ThreeAnalyz);
	temp=Grid_Check(&grid_paras,&V_park); //孤岛保护及恢复
	Protect(temp);

	Scib_Data_Tx();

	EPwm1Regs.ETCLR.bit.INT = 1;//clear ETFLG[INT]
}

Uint16  ReadAd(void)
{
	Uint16 i,Ch[10];
	float temp=0.0;
	while ((AdcaRegs.ADCINTFLG.bit.ADCINT1 == 0)||(AdcbRegs.ADCINTFLG.bit.ADCINT1 == 0)||(AdccRegs.ADCINTFLG.bit.ADCINT1 == 0)||(AdcdRegs.ADCINTFLG.bit.ADCINT1 == 0));//判断 AD是否读完
	AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;//清除AD标志
	AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
	AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
	AdcdRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

    Ch[0]= AdcaResultRegs.ADCRESULT0;//IA
    Ch[1]= AdccResultRegs.ADCRESULT0;//IC
	Ch[2]= AdcdResultRegs.ADCRESULT0;//Ua
    Ch[3]= AdcbResultRegs.ADCRESULT3;//Ub
	Ch[4]= AdcdResultRegs.ADCRESULT1;//Uc
    Ch[5]= AdccResultRegs.ADCRESULT2;//Idc
    Ch[6]= AdcbResultRegs.ADCRESULT0;//Udcp
	Ch[7]= AdcbResultRegs.ADCRESULT2;//temp
	Ch[8]= AdcbResultRegs.ADCRESULT1;//Udcn

	Udc_count&=3;

	Ia		 = offset1 - Ch[0] * 0.0293;    //A相电流,G=20A/V
	Ic		 = offset2 - Ch[1] * 0.0293;    //C相电流,G=20A/V
    Ib       = - Ic - Ia;                   //Ia+Ib+Ic=0

	Idc		 = Ch[5] * 0.0293 - offset3;    //直流电流,G=20A/V
	Vtemp    = Ch[7]* 0.001465- 3.0;        //温度

    Uab      = Ch[3]* 0.3516 - 720;
    Ubc      = Ch[4]* 0.3516 - 720;

    Ua       = (2* Uab+Ubc)* 0.3333333;
    Ub       = (Ubc-Uab)* 0.3333333;
    Uc       = (-Uab-2* Ubc)* 0.3333333;

    Udcp     =Ch[6]* 0.23443 - 480;//直流上端与中点之间电压，G=160V/V,保护2.68V
    Udcn     =Ch[8]* 0.23443 - 480;//中点与直流下端之间电压，G=160V/V,保护2.68V

	Vdcs[Udc_count++]=Udcp+Udcn;

	for(i=0;i<4;i++)
		temp +=Vdcs[i];
    Udc		 = temp * 0.25;                 //5次求平均

	return(0);  //无故障返回0
}

void CtrlProcess (void)
{
    /*电压克拉克坐标变换*/
    V_clarke.AS     =Ua;      //将实际A相电压采集值赋值给V_AS
	V_clarke.BS     =Ub;      //将实际B相电压采集值赋值给V_BS
	V_clarke.CS     =Uc;      //将实际C相电压采集值赋值给V_CS
    clarke_calc(&V_clarke);	  //clark变换函数调用,计算电压ALPHA BETA 坐标转换值
    /*电压帕克坐标变换*/
    V_park.PAlpha   = V_clarke.Valpha;  //将克拉克变换计算的ALPHA做帕克变换输入
    V_park.PBeta    = V_clarke.Vbeta;   //将克拉克变换计算的BETA做帕克变换输入
	V_park.sel = 1;					    //角度计算标志，电压PARK变换时计算角度
	park_calc(&V_park);				    //电压PARK变换
	/*电流克拉克坐标变换*/
	I_clarke.AS    =-Ia;                 //将实际A相电流采集值赋值给I_AS，电流指向里
	I_clarke.BS    =-Ib;                 //将实际B相电流采集值赋值给I_BS
	I_clarke.CS    =-Ic;                 //将实际C相电流采集值赋值给I_CS
    clarke_calc(&I_clarke);				//clark变换函数调用,计算电流ALPHA BETA 坐标转换值
	/*电流帕克坐标变换*/
	I_park.PAlpha  = I_clarke.Valpha;   //将克拉克变换计算的ALPHA做帕克变换输入
	I_park.PBeta   = I_clarke.Vbeta;    //将克拉克变换计算的BETA做帕克变换输入
	I_park.PSine   = V_park.PSine;      //电流使用电压角度
	I_park.PCosine = V_park.PCosine;
    I_park.sel = 0;						//角度计算标志，电流使用电压角度
	park_calc(&I_park);			        //电流PARK变换
	if(flg2==1)
	{
		/*外环电压控制*/
		if(Dc_BusVolt_Ref<200)	Dc_BusVolt_Ref=200;     //直流电压可控范围300-800V,取决于交流电压
		if(Dc_BusVolt_Ref>800)	Dc_BusVolt_Ref=800;

		V_pidreg.Ref = Dc_BusVolt_Ref;          //直流电压设定值
		V_pidreg.Fdb = Udc;				        //直流电压采集值
		pid_reg_calc(&V_pidreg);			    //电压外环控制&PI限幅
		/*内环电流d轴控制*/
		Id_pidreg.Ref   = V_pidreg.Out;         //外环控制输出作为内环d轴指令电流
		Id_pidreg.Fdb   = I_park.PDs;           //电流d轴作为反馈量
		pid_reg_calc(&Id_pidreg);               //内环电流d轴PI
		V_CURR_ADJ.Vd_Pidout=Id_pidreg.Out;
		/*内环电流q轴控制*/
		Iq_pidreg.Ref   = 0.0;                  //Iq为无功电流，将其参考值设置为0
		Iq_pidreg.Fdb   = I_park.PQs;
		pid_reg_calc(&Iq_pidreg);
		V_CURR_ADJ.Vq_Pidout=Iq_pidreg.Out;
		/*前馈解耦控制方式*/
		V_CURR_ADJ.Vfdbd = V_park.PDs * Vpre_rate;  //电网d轴电压，乘以变比1
		V_CURR_ADJ.Ifdbd = I_park.PDs;
		V_CURR_ADJ.Ifdbq = I_park.PQs;
		CurrControl(&V_CURR_ADJ);				    //电流内环PI控制
		/*电流反帕克坐标变换*/
		I_ipark.IPDs    = V_CURR_ADJ.Vd;			//控制器输出d轴电压
		I_ipark.IPQs    = V_CURR_ADJ.Vq;
        I_ipark.IPDs    = I_ipark.IPDs * Dis_Para.vdc_inverse;
        I_ipark.IPQs    = I_ipark.IPQs * Dis_Para.vdc_inverse;
		I_ipark.IPSine  = V_park.PSine;
		I_ipark.IPCosine= V_park.PCosine;
		ipark_calc(&I_ipark);			            //PARK反变换
		/*七段SVPWM*/
		Svgen_Mul.Alpha    = I_ipark.IPAlpha;	    //SVPWM输入alpha，beta
		Svgen_Mul.Beta     = I_ipark.IPBeta;
	}
}
void Paramcalc1(void)
{
	float temp1,temp2;long temp3;

	temp1 =Udc*Idc;//Uab* Ia - Ubc* Ic;
	if(flg2)//发电量计算
	{

		temp2 = temp1* 10-0.5;
		temp3 =(long)temp2;
		if(temp3<0) temp3=-temp3;
		ENRG_Data.Enrg += temp3;
	}

	if(Dis_Para.Count>Dis_Para.N)
	{
		Dis_Para.Ua_sum_t =Dis_Para.Ua_sum;         Dis_Para.Ua_sum=0;
		Dis_Para.Ub_sum_t =Dis_Para.Ub_sum;         Dis_Para.Ub_sum=0;
		Dis_Para.Uc_sum_t =Dis_Para.Uc_sum;         Dis_Para.Uc_sum=0;

		Dis_Para.Udc_sum_t=Dis_Para.Udc_sum;        Dis_Para.Udc_sum=0;

		Dis_Para.Ia_sum_t =Dis_Para.Ia_sum;         Dis_Para.Ia_sum=0;
		Dis_Para.Ib_sum_t =Dis_Para.Ib_sum;         Dis_Para.Ib_sum=0;
		Dis_Para.Ic_sum_t =Dis_Para.Ic_sum;         Dis_Para.Ic_sum=0;

		Dis_Para.Ia0_sum_t =Dis_Para.Ia0_sum;       Dis_Para.Ia0_sum=0;
		Dis_Para.Ib0_sum_t =Dis_Para.Ib0_sum;       Dis_Para.Ib0_sum=0;
		Dis_Para.Ic0_sum_t =Dis_Para.Ic0_sum;       Dis_Para.Ic0_sum=0;

		Dis_Para.Idc_sum_t=Dis_Para.Idc_sum;    	Dis_Para.Idc_sum=0;

		Dis_Para.P_sum_t =Dis_Para.P_sum;           Dis_Para.P_sum=0;
		Dis_Para.Pq_sum_t =Dis_Para.Pq_sum;         Dis_Para.Pq_sum=0;

		Dis_Para.Tem_sum_t =Dis_Para.Tem_sum;       Dis_Para.Tem_sum=0;

		Dis_Para.Count=0;
		Dis_Para.status |=0x01;
	}
	else
	{
		Dis_Para.Ua_sum +=Ua * Ua;
		Dis_Para.Ub_sum +=Ub * Ub;
		Dis_Para.Uc_sum +=Uc * Uc;

		Dis_Para.Udc_sum+=Udc;

		if(Dis_Para.status & 0x04)
		{
			Dis_Para.Ia_sum += Ia * Ia;
			Dis_Para.Ib_sum += Ib * Ib;
			Dis_Para.Ic_sum += Ic * Ic;
		}

		Dis_Para.Ia0_sum+=Ia;
		Dis_Para.Ic0_sum+=Ic;

		Dis_Para.Idc_sum+=Idc;

		Dis_Para.P_sum  +=temp1;//修改为线电压,交流功率
//		Dis_Para.Pq_sum -= Uab*Ic + Ubc*Ia - (Uab+Ubc)*Ib;//无功功率

		Dis_Para.Tem_sum+=Vtemp;

		Dis_Para.Count++;
	}

}

void Paramcalc2(void)
{
	Uint16 i;
	float temp1,temp2;
	int32 temp4;

	Dis_Para.Ua=sqrt(Dis_Para.Ua_sum_t * Dis_Para.Count_Ratio);
	Dis_Para.Ub=sqrt(Dis_Para.Ub_sum_t * Dis_Para.Count_Ratio);
	Dis_Para.Uc=sqrt(Dis_Para.Uc_sum_t * Dis_Para.Count_Ratio);

	Dis_Para.Udc=Dis_Para.Udc_sum_t * Dis_Para.Count_Ratio;
    if(Dis_Para.Udc< 0.9)
        Dis_Para.Udc=0.9;
	Dis_Para.vdc_inverse = 1.732/Dis_Para.Udc;

	Dis_Para.Ia=sqrt(Dis_Para.Ia_sum_t * Dis_Para.Count_Ratio);
	Dis_Para.Ib=sqrt(Dis_Para.Ib_sum_t * Dis_Para.Count_Ratio);
	Dis_Para.Ic=sqrt(Dis_Para.Ic_sum_t * Dis_Para.Count_Ratio);

	Dis_Para.Idc=Dis_Para.Idc_sum_t * Dis_Para.Count_Ratio;

	Dis_Para.P=Dis_Para.P_sum_t * Dis_Para.Count_Ratio;
	Dis_Para.Pq=Dis_Para.Pq_sum_t * Dis_Para.Count_Ratio*0.57735f;//除sqrt(3)

	Dis_Para.Tem=Dis_Para.Tem_sum_t * Dis_Para.Count_Ratio;

	R1 = Rt/(Vt-Dis_Para.Tem) * Dis_Para.Tem;  //NTC阻值
	temp2 = R1 * R25_N;
	temp1 = log(temp2) * B5025_N + T25_N;
	temp2 = 1.0f/temp1;
	temp1 = temp2-T0;
	Dis_Para.Tem = temp1;  //温度℃

	Dis_Para.PL=Dis_Para.Ua* Dis_Para.Ia + Dis_Para.Ub* Dis_Para.Ib + Dis_Para.Uc* Dis_Para.Ic;
	Dis_Para.PF=fabs(Dis_Para.P/Dis_Para.PL);
	if(Dis_Para.PF>0.999)
	    Dis_Para.PF=0.999;

	temp4 = ENRG_Data.E_Total_Dis* 0.01;

	temp1=	Dis_Para.P * 0.01;//交流功率

	if(temp1<0)	temp1 = temp1-0.3;//六舍七入
	else	temp1 = temp1 + 0.3;

	i=0;
	Dis_Para.Tx_int[i++] = P_rated;//逆变器额定功率
	Dis_Para.Tx_int[i++] = Dis_Para.Udc * 10; //直流电压[0]
	Dis_Para.Tx_int[i++] = (int)(Dis_Para.Idc * 10); //直流电流     int转换保留符号
	Dis_Para.Tx_int[i++] = Udcp*10;
	Dis_Para.Tx_int[i++] = 0;
	Dis_Para.Tx_int[i++] = Udcn*10;
	Dis_Para.Tx_int[i++] = ThreeAnalyz.Sequence;//相序
	Dis_Para.Tx_int[i++] = Dis_Para.Ua * 10;//A相电压//[6]
	Dis_Para.Tx_int[i++] = Dis_Para.Ia * 10;//A相电流
	Dis_Para.Tx_int[i++] = Dis_Para.Ub * 10;//B相电压
	Dis_Para.Tx_int[i++] = Dis_Para.Ib * 10;//B相电流
	Dis_Para.Tx_int[i++] = Dis_Para.Uc * 10;//C相电压[10]
	Dis_Para.Tx_int[i++] = Dis_Para.Ic * 10;//C相电流
	Dis_Para.Tx_int[i++] = (int)temp1;//交流功率0.1kw
	Dis_Para.Tx_int[i++] = ThreeAnalyz.Freq*100;//频率
	Dis_Para.Tx_int[i++] = Dis_Para.Tem * 10;//温度[14]
	Dis_Para.Tx_int[i++] = Fault2;//运行状态
	Dis_Para.Tx_int[i++] = P_set;//
	Dis_Para.Tx_int[i++] = 0;//
	Dis_Para.Tx_int[i++] = 0;//
	Dis_Para.Tx_int[i++] = 0;//
	Dis_Para.Tx_int[i++] = 0;//
	Dis_Para.Tx_int[i++] = temp4 & 0x0000ffff;//总发电量
	Dis_Para.Tx_int[i++] = temp4>>16;//高字//

}


void int_char(Uint16 len, Uint16 * Dest,Uint16 * Source)
{
    Uint16 i, temp1, temp2;
    for (i = 0; i < len; i++)
    {
        temp1 = (i << 1) + 3;
        temp2 = temp1 +1;
        *(Dest+temp1) = *(Source+i) >> 8;      //高字节在前
        *(Dest+temp2) = *(Source+i) & 0x00ff;
    }
}

void GetCrcCode(Uint16 len,Uint16 * str)
{
	Uint16 hi,lo;
	Uint16 x,j;
	hi=0xff;
	lo=0xff;
	for(x=0;x<len;x++)
	{
		j = lo^ (* (str+x));
		lo=hi^ModbusCRCHi[j];
		hi=ModbusCRCLo[j];
	}
	*(str+len)= lo;
	*(str+len+1)= hi;

}

void fault_reset(void)
{
    F_RS_H;
    DELAY_US(5);
    F_RS_L;
}

void fault_action(void)
{
    DisablePWM;
    fault_reset();

    flg1=0;
    flg2=0;

    TZCLR();
    Fault2=Fault1;
}

void Reset_status(void)
{
	TZCLR();                   //系统上电清除

	Id_pidreg.Ui = 0;
	Iq_pidreg.Ui = 0;
	V_pidreg.Ui = 0;

	flg1=1;flg2=1;

	rs_time=0;
}

void RESET_SCIB(void)
{
	ScibRegs.SCICTL1.bit.SWRESET=0;
	DELAY_US(1);
	ScibRegs.SCICTL1.bit.SWRESET=1;
}

void RESET_SCIC(void)
{
	ScicRegs.SCICTL1.bit.SWRESET=0;
	DELAY_US(1);
	ScicRegs.SCICTL1.bit.SWRESET=1;
}

void Protect(unsigned int s)
{
    float temp;

	switch(s)
	{
		case 1:
			if((Ua<Extre.uac_Min1)||(Ua>Extre.uac_Max3)||(Ub<Extre.uac_Min1)||(Ub>Extre.uac_Max3)||(Uc<Extre.uac_Min1)||(Uc>Extre.uac_Max3))
			{
				Fault1|=0x0001;	    //交流过压 线电压瞬时值
			}

			if(Udc>Extre.Udc_Max3)
			{
				Fault1|=0x0400;	    //母线过压 瞬时值
			}

            temp=fabs(Udcp-Udcn);
            if(temp>80)//
            {
                Fault1|=0x2000;     //中点电压不平衡
            }
            if((temp<30)&&(Fault1&0x2000))
            {
                Fault1&=0xdfff;
            }
			break;

		case 2: //孤岛
			Fault1|=0x0020;
			break;
        case 3:
            if((ThreeAnalyz.Freq<50.45)&&(ThreeAnalyz.Freq>49.55))
                Fault1&=0xffdf;
			break;
		case 4:
			if((Dis_Para.Ua>Extre.uac_Max2)||(Dis_Para.Ub>Extre.uac_Max2)||(Dis_Para.Uc>Extre.uac_Max2))
			{
				Fault1|=0x0001;     //交流过压 有效值
			}
			else if((Dis_Para.Ua<Extre.uac_Max1)&&(Dis_Para.Ub<Extre.uac_Max1)&&(Dis_Para.Uc<Extre.uac_Max1))
			{
				Fault1&=0xfffe;
			}
			if((Dis_Para.Ua<Extre.uac_Min2)||(Dis_Para.Ub<Extre.uac_Min2)||(Dis_Para.Uc<Extre.uac_Min2))
			{
				Fault1|=0x0020;     //交流欠压有效值//和孤岛共用
			}

			if(Dis_Para.Udc>Extre.Udc_Max2)
			{
				Fault1|=0x0400;     //母线过压 平均值
			}
			else if(Dis_Para.Udc<Extre.Udc_Max1)
			{
				Fault1&=0xfbff;
			}

			if(Dis_Para.Udc<Extre.Udc_Min2)
			{
//				Fault1|=0x0800;//母线欠压 平均值
			}
			else if(Dis_Para.Udc>Extre.Udc_Min3)
			{
				Fault1&=0xf7ff;
			};
            if((ThreeAnalyz.Freq > 50.55)||(ThreeAnalyz.Freq<49.45))
            {
                Fault1|=0x0020;     //频率保护
            }

			if(Dis_Para.Tem>Extre.Temp_max2)    //温度保护
			{
				Fault1|= 0x4000;
			}
			else if(Dis_Para.Tem<Extre.Temp_max1)
			{
				Fault1 &= 0xbfff;
			}
       		break;

		default:
	       	break;
	}

	if((flg2)&&(Fault1))    //故障处理
	    fault_action();
}

void WR_Flash(Uint16* x)
{Uint16 *p,data[8],i;
	p=x;
	for(i=0;i<4;i++)
	{
		data[i*2]=*(p+i);
		data[i*2+1]=(*(p+i))>>8;
	}
	if((WR_En==3)&&(Fault1 & 0x7fff))
	{
		WriteData(data,72,8);
		WR_En =0;
	}
}

void ENRG_Compute(Energy_handle E)
{int64 temp;

 temp = E->Enrg * E->Enrg_k;// 单位: 10wh
 if(temp>999999999)
   {
	E->Enrg = 200000000;
	E->Enrg_Pre = 0;
	temp = 0;
   }
 E->E_Total_Dis = temp;

 temp = E->Enrg - E->Enrg_D;
 if(temp<0)
   {
	if(temp<E->Enrg_Total_Half)
	  temp += E->Enrg_Total;
	else
	  temp = 0;
   }
 E->E_date_Dis = temp * E->Enrg_k + 0.5f;

 temp = E->Enrg - E->Enrg_M;
 if(temp<0)
   {
	if(temp<E->Enrg_Total_Half)
	  temp += E->Enrg_Total;
	else
	  temp = 0;
   }
 E->E_Month_Dis = temp * E->Enrg_k + 0.5f;

 temp = E->Enrg - E->Enrg_Y;
 if(temp<0)
   {
	if(temp<E->Enrg_Total_Half)
	  temp += E->Enrg_Total;
	else
	  temp = 0;
   }
 E->E_Year_Dis = temp * E->Enrg_k + 0.5f;
}

void Scib_Check(void)
{
	if(ScibRegs.SCIRXST.bit.RXRDY)      //接收缓冲寄存器就绪
	{
		Uart1.Rx_Data1[Uart1.Rx_Cnt++]= ScibRegs.SCIRXBUF.bit.SAR;	  //接收一个字节
		if(Uart1.Rx_Data1[0]==0x01)     //通讯地址判断
		{
		    if(Uart1.Rx_Cnt>1)
		    {
                if((Uart1.Rx_Data1[1]==0x04)||(Uart1.Rx_Data1[1]==0x05)||(Uart1.Rx_Data1[1]==0x06))
                {
                    if(Uart1.Rx_Cnt & 0x08)     //接收8个字节，包括通讯地址1个字节，功能码1个字节，寄存器地址2个字节，寄存器数量或者设置数据2个字节，CRC检验2个字节
                    {
                        Uart1.Rx_Flag=0x1;      //接收标志位置1
                        Uart1.Rx_Cnt=0;         //接收字节数计数清0
                    }
                }
                else    Uart1.Rx_Cnt=0;         //接收字节数计数清0
		    }
		}
		else Uart1.Rx_Cnt=0;
	}
    if(Uart1.Rx_Flag & 0x1)                     //485应答10mS延时
        Uart1.Tx_delay++;
}

void Scib_Data_Process(void)
{
	unsigned int temp;

    Uart1.Rx_Flag=0;                        //485接收标志位清零
    Uart1.Rx_Data1[8]=Uart1.Rx_Data1[6];    //CRC16-MODBUS检验位低8位赋值给Rx_Data1[8]
    Uart1.Rx_Data1[9]=Uart1.Rx_Data1[7];    //CRC16-MODBUS检验位高8位赋值给Rx_Data1[9]

    GetCrcCode(6,Uart1.Rx_Data1);           //查表法计算检验位CRC16-MODBUS

    if((Uart1.Rx_Data1[8] != Uart1.Rx_Data1[6])||(Uart1.Rx_Data1[9] != Uart1.Rx_Data1[7]))  //检验校验位
        Uart1.Rx_Data1[1] = 0;

    switch(Uart1.Rx_Data1[1])       //功能码
    {
        case 0x04:
                temp = (Uart1.Rx_Data1[2]<<8) + Uart1.Rx_Data1[3];
                if(temp<1000) temp=1000;
                if(temp>1023) temp=1023;
                temp=temp-1000;         //寄存器起始地址偏移量

                Uart1.Tx_Data1[2]=Uart1.Rx_Data1[5];        //发送寄存器数目
                if(Uart1.Tx_Data1[2]>24)
                    Uart1.Tx_Data1[2]=24;

                int_char(Uart1.Tx_Data1[2],Uart1.Tx_Data1,&Dis_Para.Tx_int[temp]);
                Uart1.Tx_Data1[2] = Uart1.Tx_Data1[2]<<1;   //发送字节数目

                Uart1.Tx_Num1 = 3 + Uart1.Tx_Data1[2];
                GetCrcCode(Uart1.Tx_Num1, Uart1.Tx_Data1);
                Uart1.Tx_Num1 = 2 + Uart1.Tx_Num1;          //加上校验2字节

                Uart1.Tx_Flag=0x02;
                break;
        case 0x05://开关机
				if(Uart1.Rx_Data1[4])
					Fault1 &= 0xefff;
				else
					{Fault1 |= 0x1000;DisablePWM;flg1=0;flg2=0;Fault2=Fault1;}
                Uart1.Tx_Flag=0x04;
                break;
        case 0x06://电压
				temp = Uart1.Rx_Data1[5] + Uart1.Rx_Data1[4] * 256;
				if(Uart1.Rx_Data1[3]==0xda)         //电压控制
				{
                    if(temp>800)
                        temp=800;
                    if(temp<300)
                        temp=300;

                    Dc_BusVolt_Ref = temp;
				}
				if(Uart1.Rx_Data1[3]==0xdc)         //功率 电流控制
				{
                    if(temp<1)
                        temp=1;
                    if(temp>150)
                        temp=150;
                    P_set = temp;

                    V_pidreg.OutMax = 0.22 * temp;
                    V_pidreg.OutMin = -V_pidreg.OutMax;
				}
                Uart1.Tx_Flag=0x04;
                break;
    }
}

void Scib_Data_Tx(void)
{
    if(ScibRegs.SCIRXST.bit.RXERROR)//串口错误复位
        RESET_SCIB();
    if(ScibRegs.SCICTL2.bit.TXRDY)
    {
        if(Uart1.Tx_Flag & 0x06)
            RS485_TX1;
        switch(Uart1.Tx_Flag)
        {
            case 0x02:
                    ScibRegs.SCITXBUF.all = Uart1.Tx_Data1[Uart1.Tx_Cnt++];
                    if(Uart1.Tx_Cnt==Uart1.Tx_Num1)//数据
                    {
                        Uart1.Tx_Cnt=0;
                        Uart1.Tx_Flag=0;
                    }
                    break;
            case 0x04:
                    ScibRegs.SCITXBUF.all = Uart1.Rx_Data1[Uart1.Tx_Cnt++];
                    if(Uart1.Tx_Cnt & 0x08)
                    {
                        Uart1.Tx_Cnt=0;
                        Uart1.Tx_Flag=0;
                    }
                    break;
            default:
                break;
        }
    }
}

void GPIO_Setup(void)
{
    EALLOW;
    GpioCtrlRegs.GPCMUX2.bit.GPIO93 = 0;//PWMEN1
    GpioCtrlRegs.GPEMUX1.bit.GPIO133 = 0;//PWMEN2
    GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 0;//Fault_reset
    GpioCtrlRegs.GPCMUX1.bit.GPIO70 = 0;//485CH1
    GpioCtrlRegs.GPBMUX1.bit.GPIO47 = 0;//relay1
    GpioCtrlRegs.GPBMUX2.bit.GPIO48 = 0;//relay2
    GpioCtrlRegs.GPBMUX2.bit.GPIO49 = 0;//relay3
    GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 0;//relay4
    GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 0;//unload

    GpioCtrlRegs.GPCMUX1.bit.GPIO66 = 0;//UFO
    GpioCtrlRegs.GPCMUX1.bit.GPIO67 = 0;//IFO
    GpioDataRegs.GPBCLEAR.bit.GPIO49 = 1;//relay4
    GpioDataRegs.GPBCLEAR.bit.GPIO51 = 1;//unload

    GpioDataRegs.GPCCLEAR.bit.GPIO70 = 1;//485CH1
    GpioDataRegs.GPCCLEAR.bit.GPIO93 = 1;//PWMEN1
    GpioDataRegs.GPECLEAR.bit.GPIO133 = 1;//PWMEN2
//Output
    GpioCtrlRegs.GPBDIR.bit.GPIO44 = 1;//Fault_reset
    GpioCtrlRegs.GPCDIR.bit.GPIO93 = 1;//
    GpioCtrlRegs.GPEDIR.bit.GPIO133 = 1;
    GpioCtrlRegs.GPCDIR.bit.GPIO70 = 1;//
    GpioCtrlRegs.GPBDIR.bit.GPIO47 = 1;//relay1
    GpioCtrlRegs.GPBDIR.bit.GPIO48 = 1;//relay2
    GpioCtrlRegs.GPBDIR.bit.GPIO49 = 1;//relay3
    GpioCtrlRegs.GPBDIR.bit.GPIO50 = 1;//relay4
    GpioCtrlRegs.GPBDIR.bit.GPIO51 = 1;//unload

//Input
    GpioCtrlRegs.GPCDIR.bit.GPIO66 = 0;//
    GpioCtrlRegs.GPCDIR.bit.GPIO67 = 0;//

    EDIS;
}

void I2C_Operation(void)
{Uint16 i,data[128],*p,temp;

    ReadData(data,0,128);
    temp=0;
    for(i=0;i<8;i++)
        temp +=data[i];
    if(temp==2040)//EEPROM空片检测
    {
        for(i=0;i<16;i++)
            data[i]=0;
        for(i=0;i<8;i++)
        {
            WriteData(data,i*16,16);//M24c02  每页大小为16字节   AT24c02每页为8字节  需要修改
            DELAY_US(5000);
        }
    }
    else
    {
        for(i=0;i<64;i++)
        {
            temp=i<<1;
            data[temp] +=data[temp+1]<<8;
        }
        for(i=1;i<64;i++)
        {
            temp=i*2;
            data[i] =data[temp];
        }
        /******电量数据******/
        p=(Uint16 *)(&ENRG_Data.Enrg);//dsp按照16位编址
        for(i=0;i<4;i++)
            *(p+i)= data[i+36];

        p=(Uint16 *)(&ENRG_Data.Enrg_Y);
        for(i=0;i<4;i++)
            *(p+i)= data[i+40];
        p=(Uint16 *)(&ENRG_Data.Enrg_M);
        for(i=0;i<4;i++)
            *(p+i)= data[i+44];
        p=(Uint16 *)(&ENRG_Data.Enrg_D);
        for(i=0;i<4;i++)
            *(p+i)= data[i+48];

        p=(Uint16 *)(&ENRG_Data.Year);
        *p=data[52] &= 0xff;//去掉年月日旳高字节
        ENRG_Data.Y_Update=ENRG_Data.Year;
        p=(Uint16 *)(&ENRG_Data.Month);
        *p=data[54] &= 0xff;//去掉年月日旳高字节
        ENRG_Data.M_Update=ENRG_Data.Month;
        p=(Uint16 *)(&ENRG_Data.Date);
        *p=data[56] &= 0xff;
        ENRG_Data.D_Update=ENRG_Data.Date;
    }
}

Uint16 ModbusCRCHi[]=
{
0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,
0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,
0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,
0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x00,0xc1,
0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,
0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x00,0xc1,
0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,
0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,
0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,
0x81,0x40,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,
0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,
0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,
0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,
0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,
0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,
0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,
0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,
0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,
0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,
0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,
0x80,0x41,0x00,0xc1,0x81,0x40
};

Uint16 ModbusCRCLo[]=
{
0x00,0xc0,0xc1,0x01,0xc3,0x03,0x02,0xc2,0xc6,0x06,
0x07,0xc7,0x05,0xc5,0xc4,0x04,0xcc,0x0c,0x0d,0xcd,
0x0f,0xcf,0xce,0x0e,0x0a,0xca,0xcb,0x0b,0xc9,0x09,
0x08,0xc8,0xd8,0x18,0x19,0xd9,0x1b,0xdb,0xda,0x1a,
0x1e,0xde,0xdf,0x1f,0xdd,0x1d,0x1c,0xdc,0x14,0xd4,
0xd5,0x15,0xd7,0x17,0x16,0xd6,0xd2,0x12,0x13,0xd3,
0x11,0xd1,0xd0,0x10,0xf0,0x30,0x31,0xf1,0x33,0xf3,
0xf2,0x32,0x36,0xf6,0xf7,0x37,0xf5,0x35,0x34,0xf4,
0x3c,0xfc,0xfd,0x3d,0xff,0x3f,0x3e,0xfe,0xfa,0x3a,
0x3b,0xfb,0x39,0xf9,0xf8,0x38,0x28,0xe8,0xe9,0x29,
0xeb,0x2b,0x2a,0xea,0xee,0x2e,0x2f,0xef,0x2d,0xed,
0xec,0x2c,0xe4,0x24,0x25,0xe5,0x27,0xe7,0xe6,0x26,
0x22,0xe2,0xe3,0x23,0xe1,0x21,0x20,0xe0,0xa0,0x60,
0x61,0xa1,0x63,0xa3,0xa2,0x62,0x66,0xa6,0xa7,0x67,
0xa5,0x65,0x64,0xa4,0x6c,0xac,0xad,0x6d,0xaf,0x6f,
0x6e,0xae,0xaa,0x6a,0x6b,0xab,0x69,0xa9,0xa8,0x68,
0x78,0xb8,0xb9,0x79,0xbb,0x7b,0x7a,0xba,0xbe,0x7e,
0x7f,0xbf,0x7d,0xbd,0xbc,0x7c,0xb4,0x74,0x75,0xb5,
0x77,0xb7,0xb6,0x76,0x72,0xb2,0xb3,0x73,0xb1,0x71,
0x70,0xb0,0x50,0x90,0x91,0x51,0x93,0x53,0x52,0x92,
0x96,0x56,0x57,0x97,0x55,0x95,0x94,0x54,0x9c,0x5c,
0x5d,0x9d,0x5f,0x9f,0x9e,0x5e,0x5a,0x9a,0x9b,0x5b,
0x99,0x59,0x58,0x98,0x88,0x48,0x49,0x89,0x4b,0x8b,
0x8a,0x4a,0x4e,0x8e,0x8f,0x4f,0x8d,0x4d,0x4c,0x8c,
0x44,0x84,0x85,0x45,0x87,0x47,0x46,0x86,0x82,0x42,
0x43,0x83,0x41,0x81,0x80,0x40
};

