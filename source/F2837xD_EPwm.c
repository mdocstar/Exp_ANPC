//###########################################################################
//
// FILE:   F2837xD_EPwm.c
//
// TITLE:  F2837xD EPwm Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2837xD Support Library v210 $
// $Release Date: Tue Nov  1 14:46:15 CDT 2016 $
// $Copyright: Copyright (C) 2013-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//
// Included Files
//
#include "F2837xD_device.h"
#include "F2837xD_Examples.h"

void InitEPwmGpio(void)
{
    EALLOW;
    ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = 0;     // PWM CLK select    0:200M 1:100M
    EDIS;

    EALLOW;
    //InitTzGpio
    GpioCtrlRegs.GPCPUD.bit.GPIO66 = 0;    // Enable pull-up on GPIO66 (TZ1)
    GpioCtrlRegs.GPCPUD.bit.GPIO67 = 0;
    GpioCtrlRegs.GPCCTRL.bit.QUALPRD0= 30;
    GpioCtrlRegs.GPCQSEL1.bit.GPIO66 = 1;  // Asynch input GPIO66 (TZ1)
    GpioCtrlRegs.GPCQSEL1.bit.GPIO67 = 1;//3 samples

    InputXbarRegs.INPUT1SELECT = 67;//IFO
    InputXbarRegs.INPUT2SELECT = 66;//UFO
    EDIS;

    InitEPwm1Gpio();
    InitEPwm2Gpio();
    InitEPwm3Gpio();
    InitEPwm4Gpio();
    InitEPwm5Gpio();
    InitEPwm6Gpio();
    InitEPwm7Gpio();
    InitEPwm8Gpio();
    InitEPwm9Gpio();
//    InitEPwm10Gpio();
//    InitEPwm11Gpio();
//    InitEPwm12Gpio();
}

void TZCLR(void)
{
    EALLOW;
    EPwm1Regs.TZCLR.bit.OST = 1;//解除Trip状态
    EPwm2Regs.TZCLR.bit.OST = 1;//解除Trip状态
    EPwm3Regs.TZCLR.bit.OST = 1;//解除Trip状态
    EPwm4Regs.TZCLR.bit.OST = 1;//解除Trip状态
    EPwm5Regs.TZCLR.bit.OST = 1;//解除Trip状态
    EPwm6Regs.TZCLR.bit.OST = 1;//解除Trip状态
    EPwm7Regs.TZCLR.bit.OST = 1;//解除Trip状态
    EPwm8Regs.TZCLR.bit.OST = 1;//解除Trip状态
    EPwm9Regs.TZCLR.bit.OST = 1;//解除Trip状态

    EPwm1Regs.TZOSTCLR.bit.OST1 = 1;//TZ1电流保护标志

    EPwm1Regs.TZOSTCLR.bit.OST2 = 1;//TZ2电压保护标志
    EDIS;
}

void InitEPwm(void)
{
    EPwm1Regs.TBPRD             = EPWM_TBPRD;
    EPwm1Regs.TBCTR             = 0x0000;
    EPwm1Regs.TBPHS.bit.TBPHS   = 0;
    EPwm1Regs.CMPA.bit.CMPA = 0;

    EPwm1Regs.TBCTL.bit.CLKDIV      = TB_DIV1;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV   = TB_DIV2;  //TBCLK=SYSCLK/(CLKDIV*HSPCLKDIV)
    EPwm1Regs.TBCTL.bit.SYNCOSEL    = TB_CTR_ZERO;
    EPwm1Regs.TBCTL.bit.PRDLD       = 1;
    EPwm1Regs.TBCTL.bit.CTRMODE     = 0x2;  //=2,up-down count mode
    EPwm1Regs.TBCTL.bit.PHSEN       = TB_DISABLE;
    EPwm1Regs.CMPCTL.bit.SHDWAMODE  = TB_SHADOW;        //0,shadow mode
    EPwm1Regs.CMPCTL.bit.LOADAMODE  = CC_CTR_ZERO;

    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;  //active low mode,
    EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;
    EPwm1Regs.DBCTL.bit.IN_MODE     = DBA_ALL;      //EPWM1A IN
    EPwm1Regs.DBCTL.bit.POLSEL      = DB_ACTV_HIC;      //ALC mode,a invert
    EPwm1Regs.DBCTL.bit.OUT_MODE    = DB_FULL_ENABLE;       //full enable
    EPwm1Regs.DBRED.all = 40;
    EPwm1Regs.DBFED.all = 40;

    EPwm2Regs.TBPRD             = EPWM_TBPRD;
    EPwm2Regs.TBCTR             = 0x0000;
    EPwm2Regs.TBPHS.bit.TBPHS   = 0;
    EPwm2Regs.CMPA.bit.CMPA = 0;

    EPwm2Regs.TBCTL.bit.CLKDIV      = TB_DIV1;
    EPwm2Regs.TBCTL.bit.HSPCLKDIV   = TB_DIV2;  //TBCLK=SYSCLK/(CLKDIV*HSPCLKDIV)
    EPwm2Regs.TBCTL.bit.SYNCOSEL    = TB_SYNC_IN;
    EPwm2Regs.TBCTL.bit.PRDLD       = 1;
    EPwm2Regs.TBCTL.bit.CTRMODE     = 0x2;  //=2,up-down count mode
    EPwm2Regs.TBCTL.bit.PHSEN       = TB_ENABLE;
    EPwm2Regs.CMPCTL.bit.SHDWAMODE  = TB_SHADOW;        //0,shadow mode
    EPwm2Regs.CMPCTL.bit.LOADAMODE  = CC_CTR_ZERO;

    EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;  //
    EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;
    EPwm2Regs.DBCTL.bit.IN_MODE     = DBA_ALL;      //
    EPwm2Regs.DBCTL.bit.POLSEL      = DB_ACTV_HIC;      //
    EPwm2Regs.DBCTL.bit.OUT_MODE    = DB_FULL_ENABLE;       //full enable
    EPwm2Regs.DBRED.all = 40;
    EPwm2Regs.DBFED.all = 40;


    EPwm3Regs.TBPRD             = EPWM_TBPRD;
    EPwm3Regs.TBCTR             = 0x0000;
    EPwm3Regs.TBPHS.bit.TBPHS   = 0;
    EPwm3Regs.CMPA.bit.CMPA = 0;

    EPwm3Regs.TBCTL.bit.CLKDIV      = TB_DIV1;
    EPwm3Regs.TBCTL.bit.HSPCLKDIV   = TB_DIV2;  //TBCLK=SYSCLK/(CLKDIV*HSPCLKDIV)
    EPwm3Regs.TBCTL.bit.SYNCOSEL    = TB_SYNC_IN;
    EPwm3Regs.TBCTL.bit.PRDLD       = 1;
    EPwm3Regs.TBCTL.bit.CTRMODE     = 0x2;  //=2,up-down count mode
    EPwm3Regs.TBCTL.bit.PHSEN       = TB_ENABLE;
    EPwm3Regs.CMPCTL.bit.SHDWAMODE  = TB_SHADOW;        //0,shadow mode
    EPwm3Regs.CMPCTL.bit.LOADAMODE  = CC_CTR_ZERO;

    EPwm3Regs.AQCSFRC.bit.CSFA      =AQ_SET;
    EPwm3Regs.AQCSFRC.bit.CSFB      =AQ_SET;
//    EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;
//    EPwm3Regs.AQCTLA.bit.CAD = AQ_SET;
//    EPwm3Regs.DBCTL.bit.IN_MODE     = DBA_ALL;      //
//    EPwm3Regs.DBCTL.bit.POLSEL      = DB_ACTV_LOC;      //
//    EPwm3Regs.DBCTL.bit.OUT_MODE    = DB_FULL_ENABLE;       //full enable
//    EPwm3Regs.DBRED.all = 100;
//    EPwm3Regs.DBFED.all = 100;

    EPwm4Regs.TBPRD             = EPWM_TBPRD;
    EPwm4Regs.TBCTR             = 0x0000;
    EPwm4Regs.TBPHS.bit.TBPHS   = 0;
    EPwm4Regs.CMPA.bit.CMPA = 0;

    EPwm4Regs.TBCTL.bit.CLKDIV      = TB_DIV1;
    EPwm4Regs.TBCTL.bit.HSPCLKDIV   = TB_DIV2;  //TBCLK=SYSCLK/(CLKDIV*HSPCLKDIV)
    EPwm4Regs.TBCTL.bit.SYNCOSEL    = TB_SYNC_IN;
    EPwm4Regs.TBCTL.bit.PRDLD       = 1;
    EPwm4Regs.TBCTL.bit.CTRMODE     = 0x2;  //=2,up-down count mode
    EPwm4Regs.TBCTL.bit.PHSEN       = TB_ENABLE;
    EPwm4Regs.CMPCTL.bit.SHDWAMODE  = TB_SHADOW;        //0,shadow mode
    EPwm4Regs.CMPCTL.bit.LOADAMODE  = CC_CTR_ZERO;

    EPwm4Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm4Regs.AQCTLA.bit.CAD = AQ_SET;
    EPwm4Regs.DBCTL.bit.IN_MODE     = DBA_ALL;      //
    EPwm4Regs.DBCTL.bit.POLSEL      = DB_ACTV_HIC;      //
    EPwm4Regs.DBCTL.bit.OUT_MODE    = DB_FULL_ENABLE;       //full enable
    EPwm4Regs.DBRED.all = 40;
    EPwm4Regs.DBFED.all = 40;

    EPwm5Regs.TBPRD             = EPWM_TBPRD;
    EPwm5Regs.TBCTR             = 0x0000;
    EPwm5Regs.TBPHS.bit.TBPHS   = 0;
    EPwm5Regs.CMPA.bit.CMPA = 0;

    EPwm5Regs.TBCTL.bit.CLKDIV      = TB_DIV1;
    EPwm5Regs.TBCTL.bit.HSPCLKDIV   = TB_DIV2;  //TBCLK=SYSCLK/(CLKDIV*HSPCLKDIV)
    EPwm5Regs.TBCTL.bit.SYNCOSEL    = TB_SYNC_IN;
    EPwm5Regs.TBCTL.bit.PRDLD       = 1;
    EPwm5Regs.TBCTL.bit.CTRMODE     = 0x2;  //=2,up-down count mode
    EPwm5Regs.TBCTL.bit.PHSEN       = TB_ENABLE;
    EPwm5Regs.CMPCTL.bit.SHDWAMODE  = TB_SHADOW;        //0,shadow mode
    EPwm5Regs.CMPCTL.bit.LOADAMODE  = CC_CTR_ZERO;

    EPwm5Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm5Regs.AQCTLA.bit.CAD = AQ_SET;
    EPwm5Regs.DBCTL.bit.IN_MODE     = DBA_ALL;      //
    EPwm5Regs.DBCTL.bit.POLSEL      = DB_ACTV_HIC;      //
    EPwm5Regs.DBCTL.bit.OUT_MODE    = DB_FULL_ENABLE;       //full enable
    EPwm5Regs.DBRED.all = 40;
    EPwm5Regs.DBFED.all = 40;

    EPwm6Regs.TBPRD             = EPWM_TBPRD;
    EPwm6Regs.TBCTR             = 0x0000;
    EPwm6Regs.TBPHS.bit.TBPHS   = 0;
    EPwm6Regs.CMPA.bit.CMPA = 0;

    EPwm6Regs.TBCTL.bit.CLKDIV      = TB_DIV1;
    EPwm6Regs.TBCTL.bit.HSPCLKDIV   = TB_DIV2;  //TBCLK=SYSCLK/(CLKDIV*HSPCLKDIV)
    EPwm6Regs.TBCTL.bit.SYNCOSEL    = TB_SYNC_IN;
    EPwm6Regs.TBCTL.bit.PRDLD       = 1;
    EPwm6Regs.TBCTL.bit.CTRMODE     = 0x2;  //=2,up-down count mode
    EPwm6Regs.TBCTL.bit.PHSEN       = TB_ENABLE;
    EPwm6Regs.CMPCTL.bit.SHDWAMODE  = TB_SHADOW;        //0,shadow mode
    EPwm6Regs.CMPCTL.bit.LOADAMODE  = CC_CTR_ZERO;

    EPwm6Regs.AQCSFRC.bit.CSFA      =AQ_SET;
    EPwm6Regs.AQCSFRC.bit.CSFB      =AQ_SET;
//    EPwm6Regs.AQCTLA.bit.CAU = AQ_CLEAR;
//    EPwm6Regs.AQCTLA.bit.CAD = AQ_SET;
//    EPwm6Regs.DBCTL.bit.IN_MODE     = DBA_ALL;      //
//    EPwm6Regs.DBCTL.bit.POLSEL      = DB_ACTV_LOC;      //
//    EPwm6Regs.DBCTL.bit.OUT_MODE    = DB_FULL_ENABLE;       //full enable
//    EPwm6Regs.DBRED.all = 100;
//    EPwm6Regs.DBFED.all = 100;

    EPwm7Regs.TBPRD             = EPWM_TBPRD;
    EPwm7Regs.TBCTR             = 0x0000;
    EPwm7Regs.TBPHS.bit.TBPHS   = 0;
    EPwm7Regs.CMPA.bit.CMPA = 0;

    EPwm7Regs.TBCTL.bit.CLKDIV      = TB_DIV1;
    EPwm7Regs.TBCTL.bit.HSPCLKDIV   = TB_DIV2;  //TBCLK=SYSCLK/(CLKDIV*HSPCLKDIV)
    EPwm7Regs.TBCTL.bit.SYNCOSEL    = TB_SYNC_IN;
    EPwm7Regs.TBCTL.bit.PRDLD       = 1;
    EPwm7Regs.TBCTL.bit.CTRMODE     = 0x2;  //=2,up-down count mode
    EPwm7Regs.TBCTL.bit.PHSEN       = TB_ENABLE;
    EPwm7Regs.CMPCTL.bit.SHDWAMODE  = TB_SHADOW;        //0,shadow mode
    EPwm7Regs.CMPCTL.bit.LOADAMODE  = CC_CTR_ZERO;

    EPwm7Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm7Regs.AQCTLA.bit.CAD = AQ_SET;
    EPwm7Regs.DBCTL.bit.IN_MODE     = DBA_ALL;      //
    EPwm7Regs.DBCTL.bit.POLSEL      = DB_ACTV_HIC;      //
    EPwm7Regs.DBCTL.bit.OUT_MODE    = DB_FULL_ENABLE;       //full enable
    EPwm7Regs.DBRED.all = 40;
    EPwm7Regs.DBFED.all = 40;

    EPwm8Regs.TBPRD             = EPWM_TBPRD;
    EPwm8Regs.TBCTR             = 0x0000;
    EPwm8Regs.TBPHS.bit.TBPHS   = 0;
    EPwm8Regs.CMPA.bit.CMPA = 0;

    EPwm8Regs.TBCTL.bit.CLKDIV      = TB_DIV1;
    EPwm8Regs.TBCTL.bit.HSPCLKDIV   = TB_DIV2;  //TBCLK=SYSCLK/(CLKDIV*HSPCLKDIV)
    EPwm8Regs.TBCTL.bit.SYNCOSEL    = TB_SYNC_IN;
    EPwm8Regs.TBCTL.bit.PRDLD       = 1;
    EPwm8Regs.TBCTL.bit.CTRMODE     = 0x2;  //=2,up-down count mode
    EPwm8Regs.TBCTL.bit.PHSEN       = TB_ENABLE;
    EPwm8Regs.CMPCTL.bit.SHDWAMODE  = TB_SHADOW;        //0,shadow mode
    EPwm8Regs.CMPCTL.bit.LOADAMODE  = CC_CTR_ZERO;

    EPwm8Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm8Regs.AQCTLA.bit.CAD = AQ_SET;
    EPwm8Regs.DBCTL.bit.IN_MODE     = DBA_ALL;      //
    EPwm8Regs.DBCTL.bit.POLSEL      = DB_ACTV_HIC;      //
    EPwm8Regs.DBCTL.bit.OUT_MODE    = DB_FULL_ENABLE;       //full enable
    EPwm8Regs.DBRED.all = 40;
    EPwm8Regs.DBFED.all = 40;

    EPwm9Regs.TBPRD             = EPWM_TBPRD;
    EPwm9Regs.TBCTR             = 0x0000;
    EPwm9Regs.TBPHS.bit.TBPHS   = 0;
    EPwm9Regs.CMPA.bit.CMPA = 0;

    EPwm9Regs.TBCTL.bit.CLKDIV      = TB_DIV1;
    EPwm9Regs.TBCTL.bit.HSPCLKDIV   = TB_DIV2;  //TBCLK=SYSCLK/(CLKDIV*HSPCLKDIV)
    EPwm9Regs.TBCTL.bit.SYNCOSEL    = TB_SYNC_IN;
    EPwm9Regs.TBCTL.bit.PRDLD       = 1;
    EPwm9Regs.TBCTL.bit.CTRMODE     = 0x2;  //=2,up-down count mode
    EPwm9Regs.TBCTL.bit.PHSEN       = TB_ENABLE;
    EPwm9Regs.CMPCTL.bit.SHDWAMODE  = TB_SHADOW;        //0,shadow mode
    EPwm9Regs.CMPCTL.bit.LOADAMODE  = CC_CTR_ZERO;

    EPwm9Regs.AQCSFRC.bit.CSFA      =AQ_SET;
    EPwm9Regs.AQCSFRC.bit.CSFB      =AQ_SET;
//    EPwm9Regs.AQCTLA.bit.CAU = AQ_CLEAR;
//    EPwm9Regs.AQCTLA.bit.CAD = AQ_SET;
//    EPwm9Regs.DBCTL.bit.IN_MODE     = DBA_ALL;      //
//    EPwm9Regs.DBCTL.bit.POLSEL      = DB_ACTV_LOC;      //
//    EPwm9Regs.DBCTL.bit.OUT_MODE    = DB_FULL_ENABLE;       //full enable
//    EPwm9Regs.DBRED.all = 100;
//    EPwm9Regs.DBFED.all = 100;

    EALLOW;
    EPwm1Regs.TZSEL.bit.OSHT1   = TZ_ENABLE;
    EPwm1Regs.TZCTL.bit.TZA     = TZ_FORCE_LO;
    EPwm1Regs.TZCTL.bit.TZB     = TZ_FORCE_LO;

    EPwm2Regs.TZSEL.bit.OSHT1   = TZ_ENABLE;
    EPwm2Regs.TZCTL.bit.TZA     = TZ_FORCE_LO;
    EPwm2Regs.TZCTL.bit.TZB     = TZ_FORCE_LO;

    EPwm4Regs.TZSEL.bit.OSHT1   = TZ_ENABLE;
    EPwm4Regs.TZCTL.bit.TZA     = TZ_FORCE_LO;
    EPwm4Regs.TZCTL.bit.TZB     = TZ_FORCE_LO;

    EPwm5Regs.TZSEL.bit.OSHT1   = TZ_ENABLE;
    EPwm5Regs.TZCTL.bit.TZA     = TZ_FORCE_LO;
    EPwm5Regs.TZCTL.bit.TZB     = TZ_FORCE_LO;

    EPwm7Regs.TZSEL.bit.OSHT1   = TZ_ENABLE;
    EPwm7Regs.TZCTL.bit.TZA     = TZ_FORCE_LO;
    EPwm7Regs.TZCTL.bit.TZB     = TZ_FORCE_LO;

    EPwm8Regs.TZSEL.bit.OSHT1   = TZ_ENABLE;
    EPwm8Regs.TZCTL.bit.TZA     = TZ_FORCE_LO;
    EPwm8Regs.TZCTL.bit.TZB     = TZ_FORCE_LO;

    EPwm1Regs.TZSEL.bit.OSHT2   = TZ_ENABLE;
    EDIS;

    EPwm1Regs.ETSEL.bit.INTEN = 1;
    EPwm1Regs.ETSEL.bit.INTSEL= ET_CTR_PRD;
    EPwm1Regs.ETPS.bit.INTCNT = ET_1ST;
    EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;

    EPwm1Regs.ETSEL.bit.SOCAEN=1;//  enable soc TO START ADC
    EPwm1Regs.ETSEL.bit.SOCASEL=ET_CTR_PRD;//soc at prd
    EPwm1Regs.ETPS.bit.SOCAPRD= 1;
}
//
// InitEPwm1Gpio - Initialize EPWM1 GPIOs
//
void InitEPwm1Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins
    // for reduced power consumption
    // Pull-ups can be enabled or disabled by the user.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;    // Disable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;    // Disable pull-up on GPIO1 (EPWM1B)
    // GpioCtrlRegs.GPEPUD.bit.GPIO145 = 1;    // Disable pull-up on GPIO145 (EPWM1A)
    // GpioCtrlRegs.GPEPUD.bit.GPIO146 = 1;    // Disable pull-up on GPIO146 (EPWM1B)

    //
    // Configure EPWM-1 pins using GPIO regs
    // This specifies which of the possible GPIO pins will be EPWM1 functional
    // pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B
    // GpioCtrlRegs.GPEMUX2.bit.GPIO145 = 1;   // Configure GPIO145 as EPWM1A
    // GpioCtrlRegs.GPEMUX2.bit.GPIO146 = 1;   // Configure GPIO0146 as EPWM1B

    EDIS;
}

//
// InitEPwm2Gpio - Initialize EPWM2 GPIOs
//
void InitEPwm2Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins
    // for reduced power consumption
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;    // Disable pull-up on GPIO2 (EPWM2A)
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;    // Disable pull-up on GPIO3 (EPWM2B)
    // GpioCtrlRegs.GPEPUD.bit.GPIO147 = 1;    // Disable pull-up on GPIO147 (EPWM2A)
    // GpioCtrlRegs.GPEPUD.bit.GPIO148 = 1;    // Disable pull-up on GPIO148 (EPWM2B)

    //
    // Configure EPwm-2 pins using GPIO regs
    // This specifies which of the possible GPIO pins will be EPWM2 functional pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;   // Configure GPIO3 as EPWM2B
   // GpioCtrlRegs.GPEMUX2.bit.GPIO147 = 1;   // Configure GPIO147 as EPWM2A
   // GpioCtrlRegs.GPEMUX2.bit.GPIO148 = 1;   // Configure GPIO148 as EPWM2B

    EDIS;
}

//
// InitEPwm3Gpio - Initialize EPWM3 GPIOs
//
void InitEPwm3Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins
    //   for reduced power consumption
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 1;    // Disable pull-up on GPIO4 (EPWM3A)
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 1;    // Disable pull-up on GPIO5 (EPWM3B)
    // GpioCtrlRegs.GPEPUD.bit.GPIO149 = 1;    // Disable pull-up on GPIO149 (EPWM3A)
    // GpioCtrlRegs.GPEPUD.bit.GPIO150 = 1;    // Disable pull-up on GPIO150 (EPWM3B)

    //
    // Configure EPwm-3 pins using GPIO regs
    // This specifies which of the possible GPIO pins will be EPWM3 functional pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   // Configure GPIO4 as EPWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;   // Configure GPIO5 as EPWM3B
    // GpioCtrlRegs.GPEMUX2.bit.GPIO149 = 1;   // Configure GPIO149 as EPWM3A
    // GpioCtrlRegs.GPEMUX2.bit.GPIO150 = 1;   // Configure GPIO150 as EPWM3B

    EDIS;
}

//
// InitEPwm4Gpio - Initialize EPWM4 GPIOs
//
void InitEPwm4Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins
    //   for reduced power consumption
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 1;    // Disable pull-up on GPIO6 (EPWM4A)
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 1;    // Disable pull-up on GPIO7 (EPWM4B)
    // GpioCtrlRegs.GPEPUD.bit.GPIO151 = 1;    // Disable pull-up on GPIO151 (EPWM4A)
    // GpioCtrlRegs.GPEPUD.bit.GPIO152 = 1;    // Disable pull-up on GPIO152 (EPWM4B)

     //
     // Configure EPWM-4 pins using GPIO regs
     // This specifies which of the possible GPIO pins will be EPWM4 functional
     // pins.
     // Comment out other unwanted lines.
     //
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;   // Configure GPIO6 as EPWM4A
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;   // Configure GPIO7 as EPWM4B
    // GpioCtrlRegs.GPEMUX2.bit.GPIO151 = 1;   // Configure GPIO151 as EPWM4A
    // GpioCtrlRegs.GPEMUX2.bit.GPIO152 = 1;   // Configure GPIO152 as EPWM4B

    EDIS;
}

//
// InitEPwm5Gpio - Initialize EPWM5 GPIOs
//
void InitEPwm5Gpio(void)
{
    EALLOW;
    //
    // Disable internal pull-up for the selected output pins
    //   for reduced power consumption
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 1;    // Disable pull-up on GPIO8 (EPWM5A)
    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 1;    // Disable pull-up on GPIO9 (EPWM5B)
    // GpioCtrlRegs.GPEPUD.bit.GPIO153 = 1;    // Disable pull-up on GPIO153 (EPWM5A)
    // GpioCtrlRegs.GPEPUD.bit.GPIO154 = 1;    // Disable pull-up on GPIO154 (EPWM5B)

    //
    // Configure EPWM-5 pins using GPIO regs
    // This specifies which of the possible GPIO pins will be EPWM5 functional
    // pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;   // Configure GPIO8 as EPWM5A
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1;   // Configure GPIO9 as EPWM5B
    // GpioCtrlRegs.GPEMUX2.bit.GPIO153 = 1;   // Configure GPIO153 as EPWM5A
    // GpioCtrlRegs.GPEMUX2.bit.GPIO154 = 1;   // Configure GPIO0154 as EPWM5B

    EDIS;
}

//
// InitEPwm6Gpio - Initialize EPWM6 GPIOs
//
void InitEPwm6Gpio(void)
{
    EALLOW;
    //
    // Disable internal pull-up for the selected output pins
    // for reduced power consumption
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 1;    // Disable pull-up on GPIO10 (EPWM6A)
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1;    // Disable pull-up on GPIO11 (EPWM6B)
    // GpioCtrlRegs.GPEPUD.bit.GPIO155 = 1;    // Disable pull-up on GPIO155 (EPWM6A)
    // GpioCtrlRegs.GPEPUD.bit.GPIO156 = 1;    // Disable pull-up on GPIO156 (EPWM6B)

    //
    // Configure EPWM-6 pins using GPIO regs
    // This specifies which of the possible GPIO pins will be EPWM6 functional
    // pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;   // Configure GPIO10 as EPWM6A
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1;   // Configure GPIO11 as EPWM6B
    // GpioCtrlRegs.GPEMUX2.bit.GPIO155 = 1;   // Configure GPIO155 as EPWM6A
    // GpioCtrlRegs.GPEMUX2.bit.GPIO156 = 1;   // Configure GPIO156 as EPWM6B

    EDIS;
}

//
// InitEPwm7Gpio - Initialize EPWM7 GPIOs
//
void InitEPwm7Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins
    // for reduced power consumption
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO12 = 1;    // Disable pull-up on GPIO12 (EPWM7A)
    GpioCtrlRegs.GPAPUD.bit.GPIO13 = 1;    // Disable pull-up on GPIO13 (EPWM7B)
    // GpioCtrlRegs.GPEPUD.bit.GPIO157 = 1;    // Disable pull-up on GPIO157 (EPWM7A)
    // GpioCtrlRegs.GPEPUD.bit.GPIO158 = 1;    // Disable pull-up on GPIO158 (EPWM7B)

    //
    // Configure EPWM-6 pins using GPIO regs
    // This specifies which of the possible GPIO pins will be EPWM6 functional
    // pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;   // Configure GPIO12 as EPWM7A
    GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 1;   // Configure GPIO13 as EPWM7B
    // GpioCtrlRegs.GPEMUX2.bit.GPIO157 = 1;   // Configure GPIO157 as EPWM7A
    // GpioCtrlRegs.GPEMUX2.bit.GPIO158 = 1;   // Configure GPIO158 as EPWM7B

    EDIS;
}

//
// InitEPwm8Gpio - Initialize EPWM8 GPIOs
//
void InitEPwm8Gpio(void)
{
    EALLOW;
    //
    // Disable internal pull-up for the selected output pins
    // for reduced power consumption
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO14 = 1;    // Disable pull-up on GPIO14 (EPWM8A)
    GpioCtrlRegs.GPAPUD.bit.GPIO15 = 1;    // Disable pull-up on GPIO15 (EPWM8B)
//  GpioCtrlRegs.GPEPUD.bit.GPIO159 = 1;    // Disable pull-up on GPIO159 (EPWM8A)
//  GpioCtrlRegs.GPFPUD.bit.GPIO160 = 1;    // Disable pull-up on GPIO160 (EPWM8B)

     //
     // Configure EPWM-6 pins using GPIO regs
     // This specifies which of the possible GPIO pins will be EPWM6 functional
     // pins.
     // Comment out other unwanted lines.
     //
    GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 1;   // Configure GPIO14 as EPWM8A
    GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 1;   // Configure GPIO15 as EPWM8B
    // GpioCtrlRegs.GPEMUX2.bit.GPIO159 = 1;   // Configure GPIO159 as EPWM8A
    // GpioCtrlRegs.GPFMUX1.bit.GPIO160 = 1;   // Configure GPIO160 as EPWM8B

    EDIS;
}

void InitEPwm9Gpio(void)
{
    EALLOW;
    //
    // Disable internal pull-up for the selected output pins
    // for reduced power consumption
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 1;    // Disable pull-up on GPIO16 (EPWM89A)
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 1;    // Disable pull-up on GPIO17 (EPWM9B)

    GpioCtrlRegs.GPAGMUX2.bit.GPIO16 = 1;
    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1;   // Configure GPIO16 as EPWM9A
    GpioCtrlRegs.GPAGMUX2.bit.GPIO17 = 1;
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1;   // Configure GPIO17 as EPWM9B

    EDIS;
}

void InitEPwm10Gpio(void)
{
    EALLOW;
    //
    // Disable internal pull-up for the selected output pins
    // for reduced power consumption
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 1;    // Disable pull-up on GPIO16 (EPWM89A)
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 1;    // Disable pull-up on GPIO17 (EPWM9B)

    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1;   // Configure GPIO16 as EPWM9A
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1;   // Configure GPIO17 as EPWM9B

    EDIS;
}

void InitEPwm11Gpio(void)
{
    EALLOW;
    //
    // Disable internal pull-up for the selected output pins
    // for reduced power consumption
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO20 = 1;    // Disable pull-up on GPIO16 (EPWM89A)
    GpioCtrlRegs.GPAPUD.bit.GPIO21 = 1;    // Disable pull-up on GPIO17 (EPWM9B)

    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 1;   // Configure GPIO16 as EPWM9A
    GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 1;   // Configure GPIO17 as EPWM9B

    EDIS;
}

void InitEPwm12Gpio(void)
{
    EALLOW;
    //
    // Disable internal pull-up for the selected output pins
    // for reduced power consumption
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO22 = 1;    // Disable pull-up on GPIO16 (EPWM89A)
    GpioCtrlRegs.GPAPUD.bit.GPIO23 = 1;    // Disable pull-up on GPIO17 (EPWM9B)

    GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 1;   // Configure GPIO16 as EPWM9A
    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 1;   // Configure GPIO17 as EPWM9B

    EDIS;
}

//
////
//// InitEPwm10Gpio - Initialize EPWM10 GPIOs
////
//void InitEPwm10Gpio(void)
//{
//    EALLOW;
//    //
//    // Disable internal pull-up for the selected output pins
//    // for reduced power consumption
//    // Pull-ups can be enabled or disabled by the user.
//    // This will enable the pullups for the specified pins.
//    // Comment out other unwanted lines.
//    //
//    GpioCtrlRegs.GPFPUD.bit.GPIO163 = 1;    // Disable pull-up on GPIO163 (EPWM10A)
//    GpioCtrlRegs.GPFPUD.bit.GPIO164 = 1;    // Disable pull-up on GPIO164 (EPWM10B)
//
//    //
//    // Configure EPWM-6 pins using GPIO regs
//    // This specifies which of the possible GPIO pins will be EPWM6 functional
//    // pins.
//    // Comment out other unwanted lines.
//    //
//    GpioCtrlRegs.GPFMUX1.bit.GPIO163 = 1;   // Configure GPIO163 as EPWM10A
//    GpioCtrlRegs.GPFMUX1.bit.GPIO164 = 1;   // Configure GPIO164 as EPWM10B
//
//    EDIS;
//}
//
////
//// InitEPwm11Gpio - Initialize EPWM11 GPIOs
////
//void InitEPwm11Gpio(void)
//{
//    EALLOW;
//    //
//    // Disable internal pull-up for the selected output pins
//    // for reduced power consumption
//    // Pull-ups can be enabled or disabled by the user.
//    // This will enable the pullups for the specified pins.
//    // Comment out other unwanted lines.
//    //
//    GpioCtrlRegs.GPFPUD.bit.GPIO165 = 1;    // Disable pull-up on GPIO165 (EPWM11A)
//    GpioCtrlRegs.GPFPUD.bit.GPIO166 = 1;    // Disable pull-up on GPIO166 (EPWM11B)
//
//    //
//    // Configure EPWM-6 pins using GPIO regs
//    // This specifies which of the possible GPIO pins will be EPWM6 functional
//    // pins.
//    // Comment out other unwanted lines.
//    //
//    GpioCtrlRegs.GPFMUX1.bit.GPIO165 = 1;   // Configure GPIO165 as EPWM11A
//    GpioCtrlRegs.GPFMUX1.bit.GPIO166 = 1;   // Configure GPIO166 as EPWM11B
//
//    EDIS;
//}
//
////
//// InitEPwm12Gpio - Initialize EPWM12 GPIOs
////
//void InitEPwm12Gpio(void)
//{
//    EALLOW;
//    //
//    // Disable internal pull-up for the selected output pins
//    // for reduced power consumption
//    // Pull-ups can be enabled or disabled by the user.
//    // This will enable the pullups for the specified pins.
//    // Comment out other unwanted lines.
//    //
//    GpioCtrlRegs.GPFPUD.bit.GPIO167 = 1;    // Disable pull-up on GPIO167 (EPWM12A)
//    GpioCtrlRegs.GPFPUD.bit.GPIO168 = 1;    // Disable pull-up on GPIO168 (EPWM12B)
//
//    //
//    // Configure EPWM-6 pins using GPIO regs
//    // This specifies which of the possible GPIO pins will be EPWM6 functional
//    // pins.
//    // Comment out other unwanted lines.
//    //
//    GpioCtrlRegs.GPFMUX1.bit.GPIO167 = 1;   // Configure GPIO167 as EPWM12A
//    GpioCtrlRegs.GPFMUX1.bit.GPIO168 = 1;   // Configure GPIO168 as EPWM12B
//
//    EDIS;
//}
