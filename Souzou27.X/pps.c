// PPS(PERIPHERAL PIN SELECT)設定
// 詳細はデータシート160p
#include "common.h"

//  (注) 出力は今のところ PWM と TX のみ対応
void set_outputpps( const unsigned char mode, const unsigned char porta,const unsigned char portb, const unsigned char portc)
{
    unsigned char sbits = 0;    
    if( mode == PWM1 ) sbits = 0b01100; // CCP1
    if( mode == PWM2 ) sbits = 0b01101; // CCP2
    if( mode == PWM3 ) sbits = 0b01110; // CCP3
    if( mode == PWM4 ) sbits = 0b01111; // CCP4
    if( mode == TX ) sbits = 0b10100; // TX
    
    if( porta & 0b00100000 ) RA5PPS = sbits;
    if( porta & 0b00010000 ) RA4PPS = sbits;
    // RA3 は MCLR/Vpp 固定
    if( porta & 0b00000100 ) RA2PPS = sbits;
    // RA1 は ICSPCLK 固定
    // RA0 は ICSPDAT 固定

    if( portb & 0b10000000 ) RB7PPS = sbits;
    if( portb & 0b01000000 ) RB6PPS = sbits;
    if( portb & 0b00100000 ) RB5PPS = sbits;
    if( portb & 0b00010000 ) RB4PPS = sbits;

    if( portc & 0b10000000 ) RC7PPS = sbits;
    if( portc & 0b01000000 ) RC6PPS = sbits;
    if( portc & 0b00100000 ) RC5PPS = sbits;
    if( portc & 0b00010000 ) RC4PPS = sbits;
    if( portc & 0b00001000 ) RC3PPS = sbits;
    if( portc & 0b00000100 ) RC2PPS = sbits;
    if( portc & 0b00000010 ) RC1PPS = sbits;
    if( portc & 0b00000001 ) RC0PPS = sbits;
}


// (注) 入力は今のところ RX のみ対応
void set_inputpps( const unsigned char mode, const unsigned char porta,const unsigned char portb, const unsigned char portc)
{
    unsigned char sbits = 0;
    if( porta & 0b00100000 ) sbits = 0b00101;
    if( porta & 0b00010000 ) sbits = 0b00100;
    // RA3 は MCLR/Vpp 固定
    if( porta & 0b00000100 ) sbits = 0b00010;
    // RA1 は ICSPCLK 固定
    // RA0 は ICSPDAT 固定

    if( portb & 0b10000000 ) sbits = 0b01111;
    if( portb & 0b01000000 ) sbits = 0b01110;
    if( portb & 0b00100000 ) sbits = 0b01101;
    if( portb & 0b00010000 ) sbits = 0b01100;

    if( portc & 0b10000000 ) sbits = 0b10111;
    if( portc & 0b01000000 ) sbits = 0b10110;
    if( portc & 0b00100000 ) sbits = 0b10101;
    if( portc & 0b00010000 ) sbits = 0b10100;
    if( portc & 0b00001000 ) sbits = 0b10011;
    if( portc & 0b00000100 ) sbits = 0b10010;
    if( portc & 0b00000010 ) sbits = 0b10001;
    if( portc & 0b00000001 ) sbits = 0b10000;
    
    if( mode == RX ){
        RXPPS = sbits;
        TRISA |=  porta;
        TRISB |=  portb;
        TRISC |=  portc;
    }
}