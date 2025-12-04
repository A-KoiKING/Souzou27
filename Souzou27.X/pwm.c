#include "common.h"

char pwm_status[PWM_NUM+1];
char pwm_timer2 = 0;
char pwm_timer4 = 0;
char pwm_timer6 = 0;

void init_ccp1(const unsigned char tsel)
{
    CCP1CONbits.CCP1MODE = 0b1111 ; // PWMモード
    CCPTMRSbits.C1TSEL = tsel; // タイマー接続
    CCP1CONbits.CCP1EN = 1; // CCPモジュール有効化
}

void init_ccp2(const unsigned char tsel)
{
    CCP2CONbits.CCP2MODE = 0b1111 ; // PWMモード
    CCPTMRSbits.C2TSEL = tsel; // タイマー接続
    CCP2CONbits.CCP2EN = 1; // CCPモジュール有効化
}

void init_ccp3(const unsigned char tsel)
{
    CCP3CONbits.CCP3MODE = 0b1111 ; // PWMモード
    CCPTMRSbits.C3TSEL = tsel; // タイマー接続
    CCP3CONbits.CCP3EN = 1; // CCPモジュール有効化
}

void init_ccp4(const unsigned char tsel)
{
    CCP4CONbits.CCP4MODE = 0b1111 ; // PWMモード
    CCPTMRSbits.C4TSEL = tsel; // タイマー接続
    CCP4CONbits.CCP4EN = 1; // CCPモジュール有効化
}

// タイマー2、4、6のクロックは FOSC/4 固定
void start_timer2(void)
{
    T2CONbits.T2CKPS = 0b11; // prescale : 64
    TMR2 = 0;
    T2CONbits.TMR2ON = 1;
}

void start_timer4(void)
{
    T4CONbits.T4CKPS = 0b11; // prescale : 64
    TMR4 = 0;
    T4CONbits.TMR4ON = 1;
}

void start_timer6(void)
{
    T6CONbits.T6CKPS = 0b11; // prescale : 64
    TMR6 = 0;
    T6CONbits.TMR6ON = 1;
}

void init_pwm_impl(const unsigned char no)
{ 
    unsigned char porta = 0;
    unsigned char portb = 0;
    unsigned char portc = 0;
    
    unsigned char mode = PWM1+no-1;
    
    pwm_status[no] = PWM_DISABLE;

    unsigned char timer = 0;
    if( ! pwm_timer2 ) timer = 2;
    else if( ! pwm_timer4 ) timer = 4;
    else if( ! pwm_timer6 ) timer = 6;
    else return;

    unsigned char num = get_pinMode(mode,&porta,&portb,&portc);
    if( ! num ) return;

    pwm_status[no] = PWM_ENABLE;
        
    unsigned char tsel = 0;
    if( timer == 2 ){
        pwm_timer2 = no;
        tsel = 0b01;
    }
    if( timer == 4 ){
        pwm_timer4 = no;
        tsel = 0b10;
    }
    if( timer == 6 ){
        pwm_timer6 = no;
        tsel = 0b11;
    }
    
    printf("-----\r\nPWM%d:\r\n",no);
    printf("timer = %d, portA = 0x%x, portB = 0x%x, portC = 0x%x\r\n",timer,porta,portb,portc);
    
    set_outputpps(mode,porta,portb,portc);

    if( mode == PWM1 ) init_ccp1(tsel);
    if( mode == PWM2 ) init_ccp2(tsel);
    if( mode == PWM3 ) init_ccp3(tsel);
    if( mode == PWM4 ) init_ccp4(tsel);

    if( timer == 2 ) start_timer2();
    if( timer == 4 ) start_timer4();
    if( timer == 6 ) start_timer6();
}

void init_pwm(void)
{
    for(unsigned char i=1; i<=PWM_NUM; ++i ) init_pwm_impl(i);
    
    pwm1(PWM_DEFAULT_PERIOD,PWM_DEFAULT_WIDTH);
    pwm2(PWM_DEFAULT_PERIOD,PWM_DEFAULT_WIDTH);
    pwm3(PWM_DEFAULT_PERIOD,PWM_DEFAULT_WIDTH);
    pwm4(PWM_DEFAULT_PERIOD,PWM_DEFAULT_WIDTH);
}

unsigned short set_timer(const unsigned char no, const unsigned short period, const unsigned short width)
{
    unsigned short period2 = (period > 16384 ? 16384 : period);
    // 周期(秒)/(4*prescale)*FOSC-1 = 周期(マイクロ秒)/prescale-1
    unsigned char pr = (unsigned char)(period2/64-1);
    if(pwm_timer2 == no) PR2 = pr;
    else if(pwm_timer4 == no) PR4 = pr;
    else if(pwm_timer6 == no) PR6 = pr;
    // = パルス幅(秒)/prescale*FOSC = パルス幅(マイクロ秒)/16
    return (period2 < width ? period2/16 : width/16); 
}

void pwm1(const unsigned short period, const unsigned short width)
{
    if( pwm_status[1] == PWM_DISABLE ) return;
    CCPR1 = set_timer(1,period,width);
}

void pwm2(const unsigned short period, const unsigned short width)
{
    if( pwm_status[2] == PWM_DISABLE ) return;
    CCPR2 = set_timer(2,period,width);
}

void pwm3(const unsigned short period, const unsigned short width)
{
    if( pwm_status[3] == PWM_DISABLE ) return;
    CCPR3 = set_timer(3,period,width);
}

void pwm4(const unsigned short period, const unsigned short width)
{
    if( pwm_status[4] == PWM_DISABLE ) return;
    CCPR4 = set_timer(4,period,width);
}
