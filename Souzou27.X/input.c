#include "common.h"

void init_input(void)
{
    unsigned char porta = 0;
    unsigned char portb = 0;
    unsigned char portc = 0;
    
    unsigned char num = get_pinMode(INPUT,&porta,&portb,&portc);
    if( num )
    {
        TRISA |= porta;
        TRISB |= portb;
        TRISC |= portc;
        printf("-----\r\nINPUT:\r\n");
        printf("portA = 0x%x, portB = 0x%x, portC = 0x%x\r\n", porta, portb, portc);
    }
    
    num = get_pinMode(INPUT_PULLUP,&porta,&portb,&portc);
    if( num )
    {
        TRISA |= porta;
        TRISB |= portb;
        TRISC |= portc;
        WPUA  |= porta;
        WPUB  |= portb;
        WPUC  |= portc;
        printf("-----\r\nINPUT_PULLUP:\r\n");
        printf("portA = 0x%x, portB = 0x%x, portC = 0x%x\r\n", porta, portb, portc);
    }
    
}