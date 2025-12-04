#pragma once

#include <xc.h>
#include "../include/proc/pic16f18346.h"

#include "adc.h"
#include "input.h"
#include "pin.h"
#include "pps.h"
#include "pwm.h"
#include "uart.h"


#define _XTAL_FREQ 4000000

enum
{
    OUTPUT=0,
    INPUT,
    INPUT_PULLUP,
    ADC,
    PWM1,
    PWM2,
    PWM3,
    PWM4,
    VDD,
    MCLR,
    TX,
    RX,
    ICSPCLK,
    ICSPDAT,
    VSS
};

enum
{
    PIN01_VDD = 1,
    PIN02_RA5,
    PIN03_RA4,
    PIN04_RA3,
    PIN05_RC5,
    PIN06_RC4,
    PIN07_RC3,
    PIN08_RC6,
    PIN09_RC7,
    PIN10_RB7,

    PIN11_RB6,
    PIN12_RB5,
    PIN13_RB4,
    PIN14_RC2,
    PIN15_RC1,
    PIN16_RC0,
    PIN17_RA2,
    PIN18_RA1,
    PIN19_RA0,
    PIN20_VSS
};