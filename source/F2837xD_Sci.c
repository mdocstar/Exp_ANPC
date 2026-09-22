//###########################################################################
//
// FILE:   F2837xD_Sci.c
//
// TITLE:  F2837xD SCI Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2837xD Support Library v190 $
// $Release Date: Mon Feb  1 16:51:57 CST 2016 $
// $Copyright: Copyright (C) 2013-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "F2837xD_device.h"     // F2837xD Headerfile Include File
#include "F2837xD_Examples.h"   // F2837xD Examples Include File

void InitSci(void)
{
	// Initialize SCI-B:
   ScibRegs.SCICCR.all =0x0007;    // 1 stop bit,  No loopback
                                   // No parity,8 char bits,
                                   // async mode, idle-line protocol
   ScibRegs.SCICTL1.all =0x0003;   // enable TX, RX, internal SCICLK,Disable RX ERR, SLEEP, TXWAKE
   ScibRegs.SCIHBAUD.all    =0x0002;
   ScibRegs.SCILBAUD.all    =0x008B;
   ScibRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset


// Initialize SCI-c:
   ScicRegs.SCICCR.all =0x0007;    // 1 stop bit,  No loopback, No parity,8 char bits,
                                   // async mode, idle-line protocol
   ScicRegs.SCICTL1.all =0x0003;   // enable TX, RX, internal SCICLK,Disable RX ERR, SLEEP, TXWAKE
   ScicRegs.SCIHBAUD.all    =0x0002;
   ScicRegs.SCILBAUD.all    =0x008B;
   ScicRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
}

void InitScibGpio()
{
    EALLOW;
	GpioCtrlRegs.GPBGMUX2.bit.GPIO54 = 1;
	GpioCtrlRegs.GPBGMUX2.bit.GPIO55 = 1;
	GpioCtrlRegs.GPBMUX2.bit.GPIO54  = 2;
	GpioCtrlRegs.GPBMUX2.bit.GPIO55  = 2;
    EDIS;
}
void InitScicGpio()
{
    EALLOW;
	GpioCtrlRegs.GPBMUX2.bit.GPIO56  = 2;//SCITXDC
	GpioCtrlRegs.GPBMUX2.bit.GPIO57  = 2;//SCIRXDC
	GpioCtrlRegs.GPBGMUX2.bit.GPIO56 = 1;
	GpioCtrlRegs.GPBGMUX2.bit.GPIO57 = 1;
    EDIS;
}
