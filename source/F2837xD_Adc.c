//###########################################################################
//
// FILE:   F2837xD_Adc.c
//
// TITLE:  F2837xD Adc Support Functions.
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

//
// AdcSetMode - Set the resolution and signalmode for a given ADC. This will
//              ensure that the correct trim is loaded.
//
void AdcSetMode(Uint16 adc, Uint16 resolution, Uint16 signalmode)
{
    Uint16 adcOffsetTrimOTPIndex; //index into OTP table of ADC offset trims
    Uint16 adcOffsetTrim;         //temporary ADC offset trim

    //
    //re-populate INL trim
    //
    CalAdcINL(adc);

    if(0xFFFF != *((Uint16*)GetAdcOffsetTrimOTP))
    {
        //
        //offset trim function is programmed into OTP, so call it
        //

        //
        //calculate the index into OTP table of offset trims and call
        //function to return the correct offset trim
        //
        adcOffsetTrimOTPIndex = 4*adc + 2*resolution + 1*signalmode;
        adcOffsetTrim = (*GetAdcOffsetTrimOTP)(adcOffsetTrimOTPIndex);
    }
    else
    {
        //
        //offset trim function is not populated, so set offset trim to 0
        //
        adcOffsetTrim = 0;
    }

    //
    //Apply the resolution and signalmode to the specified ADC.
    //Also apply the offset trim and, if needed, linearity trim correction.
    //
    switch(adc)
    {
        case ADC_ADCA:
            AdcaRegs.ADCCTL2.bit.RESOLUTION = resolution;
            AdcaRegs.ADCCTL2.bit.SIGNALMODE = signalmode;
            AdcaRegs.ADCOFFTRIM.all = adcOffsetTrim;
            if(ADC_RESOLUTION_12BIT == resolution)
            {
                //
                //12-bit linearity trim workaround
                //
                AdcaRegs.ADCINLTRIM1 &= 0xFFFF0000;
                AdcaRegs.ADCINLTRIM2 &= 0xFFFF0000;
                AdcaRegs.ADCINLTRIM4 &= 0xFFFF0000;
                AdcaRegs.ADCINLTRIM5 &= 0xFFFF0000;
            }
        break;
        case ADC_ADCB:
            AdcbRegs.ADCCTL2.bit.RESOLUTION = resolution;
            AdcbRegs.ADCCTL2.bit.SIGNALMODE = signalmode;
            AdcbRegs.ADCOFFTRIM.all = adcOffsetTrim;
            if(ADC_RESOLUTION_12BIT == resolution)
            {
                //
                //12-bit linearity trim workaround
                //
                AdcbRegs.ADCINLTRIM1 &= 0xFFFF0000;
                AdcbRegs.ADCINLTRIM2 &= 0xFFFF0000;
                AdcbRegs.ADCINLTRIM4 &= 0xFFFF0000;
                AdcbRegs.ADCINLTRIM5 &= 0xFFFF0000;
            }
        break;
        case ADC_ADCC:
            AdccRegs.ADCCTL2.bit.RESOLUTION = resolution;
            AdccRegs.ADCCTL2.bit.SIGNALMODE = signalmode;
            AdccRegs.ADCOFFTRIM.all = adcOffsetTrim;
            if(ADC_RESOLUTION_12BIT == resolution)
            {
                //
                //12-bit linearity trim workaround
                //
                AdccRegs.ADCINLTRIM1 &= 0xFFFF0000;
                AdccRegs.ADCINLTRIM2 &= 0xFFFF0000;
                AdccRegs.ADCINLTRIM4 &= 0xFFFF0000;
                AdccRegs.ADCINLTRIM5 &= 0xFFFF0000;
            }
        break;
        case ADC_ADCD:
            AdcdRegs.ADCCTL2.bit.RESOLUTION = resolution;
            AdcdRegs.ADCCTL2.bit.SIGNALMODE = signalmode;
            AdcdRegs.ADCOFFTRIM.all = adcOffsetTrim;
            if(ADC_RESOLUTION_12BIT == resolution)
            {
                //
                //12-bit linearity trim workaround
                //
                AdcdRegs.ADCINLTRIM1 &= 0xFFFF0000;
                AdcdRegs.ADCINLTRIM2 &= 0xFFFF0000;
                AdcdRegs.ADCINLTRIM4 &= 0xFFFF0000;
                AdcdRegs.ADCINLTRIM5 &= 0xFFFF0000;
            }
        break;
    }
}

//
// CalAdcINL - Loads INL trim values from OTP into the trim registers of the
//             specified ADC. Use only as part of AdcSetMode function, since
//             linearity trim correction is needed for some modes.
//
void CalAdcINL(Uint16 adc)
{
    switch(adc)
    {
        case ADC_ADCA:
            if(0xFFFF != *((Uint16*)CalAdcaINL))
            {
                //
                //trim function is programmed into OTP, so call it
                //
                (*CalAdcaINL)();
            }
            else
            {
                //
                //do nothing, no INL trim function populated
                //
            }
            break;
        case ADC_ADCB:
            if(0xFFFF != *((Uint16*)CalAdcbINL))
            {
                //
                //trim function is programmed into OTP, so call it
                //
                (*CalAdcbINL)();
            }
            else
            {
                //
                //do nothing, no INL trim function populated
                //
            }
            break;
        case ADC_ADCC:
            if(0xFFFF != *((Uint16*)CalAdccINL))
            {
                //
                //trim function is programmed into OTP, so call it
                //
                (*CalAdccINL)();
            }
            else
            {
                //
                //do nothing, no INL trim function populated
                //
            }
            break;
        case ADC_ADCD:
            if(0xFFFF != *((Uint16*)CalAdcdINL))
            {
                //
                //trim function is programmed into OTP, so call it
                //
                (*CalAdcdINL)();
            }
            else
            {
                //
                //do nothing, no INL trim function populated
                //
            }
            break;
    }
}

void InitAdc()
{
    //Uint16 i;

    EALLOW;
    AdcaRegs.ADCCTL2.bit.PRESCALE   = 6; //set ADCCLK divider to ---SYSCLK/4
    AdcaRegs.ADCCTL2.bit.RESOLUTION = 0;
    AdcaRegs.ADCCTL2.bit.SIGNALMODE = 0;
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;

    AdcbRegs.ADCCTL2.bit.PRESCALE   = 6;
    AdcbRegs.ADCCTL2.bit.RESOLUTION = 0;
    AdcbRegs.ADCCTL2.bit.SIGNALMODE = 0;
    AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1;

    AdccRegs.ADCCTL2.bit.PRESCALE   = 6;
    AdccRegs.ADCCTL2.bit.RESOLUTION = 0;
    AdccRegs.ADCCTL2.bit.SIGNALMODE = 0;
    AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1;

    AdcdRegs.ADCCTL2.bit.PRESCALE   = 6;
    AdcdRegs.ADCCTL2.bit.RESOLUTION = 0;
    AdcdRegs.ADCCTL2.bit.SIGNALMODE = 0;
    AdcdRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcdRegs.ADCCTL1.bit.ADCPWDNZ = 1;

    //delay for > 1ms to allow ADC time to power up
    /*for(i = 0; i < 1000; i++){
        asm("   RPT#255 || NOP");
    }*/
    DELAY_US(1000);

    AdcaRegs.ADCSOC0CTL.bit.CHSEL     = 5;    //Ia
    AdcaRegs.ADCSOC0CTL.bit.ACQPS     = 31;   //  32 SYSCLK
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL   = 5;
    AdcaRegs.ADCINTSEL1N2.bit.INT1CONT = 0;
    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0;
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

    AdcbRegs.ADCSOC0CTL.bit.CHSEL     = 0;    // Udcp
    AdcbRegs.ADCSOC0CTL.bit.ACQPS     = 31;
    AdcbRegs.ADCSOC0CTL.bit.TRIGSEL   = 5;

    AdcbRegs.ADCSOC1CTL.bit.CHSEL     = 15;    // Udcn
    AdcbRegs.ADCSOC1CTL.bit.ACQPS     = 31;
    AdcbRegs.ADCSOC1CTL.bit.TRIGSEL   = 5;

    AdcbRegs.ADCSOC2CTL.bit.CHSEL     = 2;    //temp
    AdcbRegs.ADCSOC2CTL.bit.ACQPS     = 31;
    AdcbRegs.ADCSOC2CTL.bit.TRIGSEL   = 5;

    AdcbRegs.ADCSOC3CTL.bit.CHSEL     = 3;    //Ub
    AdcbRegs.ADCSOC3CTL.bit.ACQPS     = 31;
    AdcbRegs.ADCSOC3CTL.bit.TRIGSEL   = 5;

    AdcbRegs.ADCINTSEL1N2.bit.INT1CONT = 0;
    AdcbRegs.ADCINTSEL1N2.bit.INT1SEL = 3;
    AdcbRegs.ADCINTSEL1N2.bit.INT1E = 1;
    AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

    AdccRegs.ADCSOC0CTL.bit.CHSEL     = 2;    //Ic
    AdccRegs.ADCSOC0CTL.bit.ACQPS     = 31;
    AdccRegs.ADCSOC0CTL.bit.TRIGSEL   = 5;

    AdccRegs.ADCSOC1CTL.bit.CHSEL     = 4;    //Ib
    AdccRegs.ADCSOC1CTL.bit.ACQPS     = 31;
    AdccRegs.ADCSOC1CTL.bit.TRIGSEL   = 5;

    AdccRegs.ADCSOC2CTL.bit.CHSEL     = 3;    //Idc
    AdccRegs.ADCSOC2CTL.bit.ACQPS     = 31;
    AdccRegs.ADCSOC2CTL.bit.TRIGSEL   = 5;
    AdccRegs.ADCINTSEL1N2.bit.INT1CONT = 0;
    AdccRegs.ADCINTSEL1N2.bit.INT1SEL = 2;
    AdccRegs.ADCINTSEL1N2.bit.INT1E = 1;
    AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

    AdcdRegs.ADCSOC0CTL.bit.CHSEL     = 2;    //Ua
    AdcdRegs.ADCSOC0CTL.bit.ACQPS     = 31;
    AdcdRegs.ADCSOC0CTL.bit.TRIGSEL   = 5;

    AdcdRegs.ADCSOC1CTL.bit.CHSEL     = 0;    //Uc
    AdcdRegs.ADCSOC1CTL.bit.ACQPS     = 31;
    AdcdRegs.ADCSOC1CTL.bit.TRIGSEL   = 5;
    AdcdRegs.ADCINTSEL1N2.bit.INT1CONT = 0;
    AdcdRegs.ADCINTSEL1N2.bit.INT1SEL = 1;
    AdcdRegs.ADCINTSEL1N2.bit.INT1E = 1;
    AdcdRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

    EDIS;
}
//
// End of file
//
