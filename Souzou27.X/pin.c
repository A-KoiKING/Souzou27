#include "common.h"

unsigned char pin_mode[21]={0};

void init_pinMode(void)
{
    pin_mode[PIN01_VDD] = VDD; // VDD 固定
    pin_mode[PIN02_RA5] = OUTPUT;
    pin_mode[PIN03_RA4] = OUTPUT;
    pin_mode[PIN04_RA3] = MCLR; // MCLR/Vpp 固定
    pin_mode[PIN05_RC5] = OUTPUT;
    pin_mode[PIN06_RC4] = OUTPUT;
    pin_mode[PIN07_RC3] = OUTPUT;
    pin_mode[PIN08_RC6] = OUTPUT;
    pin_mode[PIN09_RC7] = OUTPUT;
    pin_mode[PIN10_RB7] = OUTPUT;
    
    pin_mode[PIN11_RB6] = OUTPUT;
    pin_mode[PIN12_RB5] = OUTPUT;
    pin_mode[PIN13_RB4] = OUTPUT;
    pin_mode[PIN14_RC2] = OUTPUT;
    pin_mode[PIN15_RC1] = OUTPUT;
    pin_mode[PIN16_RC0] = OUTPUT;
    pin_mode[PIN17_RA2] = OUTPUT;
    pin_mode[PIN18_RA1] = ICSPCLK; // ICSPCLK 固定
    pin_mode[PIN19_RA0] = ICSPDAT; // ICSPDAT 固定
    pin_mode[PIN20_VSS] = VSS; // VSS 固定
}

void pinMode(const unsigned char pinno, const unsigned char mode)
{
    if(pinno > 20 ) return;
    if(pinno == PIN01_VDD ) return; // VDD固定
    if(pinno == PIN04_RA3 ) return; // MCLR/Vpp 固定
    if(pinno == PIN18_RA1 ) return; // ICSPCLK 固定
    if(pinno == PIN19_RA0 ) return; // ICSPDAT 固定
    if(pinno == PIN20_VSS ) return; // VSS 固定

    pin_mode[pinno] = mode;    
}

unsigned char get_pinMode(const unsigned char mode, unsigned char* const porta,unsigned char* const portb, unsigned char* const portc)
{
    unsigned char num = 0;
    *porta = 0;
    *portb = 0;
    *portc = 0;
    if( pin_mode[PIN02_RA5] == mode ) {*porta |= 0b00100000; ++num; }
    if( pin_mode[PIN03_RA4] == mode ) {*porta |= 0b00010000; ++num; }
    // RA3 は MCLR/Vpp 固定
    if( pin_mode[PIN17_RA2] == mode ) {*porta |= 0b00000100; ++num; }
    // RA1 は ICSPCLK 固定
    // RA0 は ICSPDAT 固定

    if( pin_mode[PIN10_RB7] == mode ) {*portb |= 0b10000000; ++num; }
    if( pin_mode[PIN11_RB6] == mode ) {*portb |= 0b01000000; ++num; }
    if( pin_mode[PIN12_RB5] == mode ) {*portb |= 0b00100000; ++num; }
    if( pin_mode[PIN13_RB4] == mode ) {*portb |= 0b00010000; ++num; }
    
    if( pin_mode[PIN09_RC7] == mode ) {*portc |= 0b10000000; ++num; }
    if( pin_mode[PIN08_RC6] == mode ) {*portc |= 0b01000000; ++num; }
    if( pin_mode[PIN05_RC5] == mode ) {*portc |= 0b00100000; ++num; }
    if( pin_mode[PIN06_RC4] == mode ) {*portc |= 0b00010000; ++num; }
    if( pin_mode[PIN07_RC3] == mode ) {*portc |= 0b00001000; ++num; }
    if( pin_mode[PIN14_RC2] == mode ) {*portc |= 0b00000100; ++num; }
    if( pin_mode[PIN15_RC1] == mode ) {*portc |= 0b00000010; ++num; }
    if( pin_mode[PIN16_RC0] == mode ) {*portc |= 0b00000001; ++num; }
    
    return num;
}
