#include "common.h"

volatile unsigned char adc_status;
volatile unsigned short adc_value[ADC_MAXCH+1];
volatile unsigned char adc_chn[ADC_MAXCH];
volatile unsigned short adc_pin[ADC_MAXCH];
volatile unsigned char adc_idx;
volatile unsigned char adc_maxidx;

void adc_isr(void)
{
    if( adc_status == ADC_GO ){
            
        if( ADCON0bits.GO_nDONE == 0 ){

            // 結果取得
            adc_value[adc_pin[adc_idx]] = ADRES;

            ++adc_idx;
            if(adc_idx >= adc_maxidx) adc_idx = 0;

            // チャンネル変更
            ADCON0bits.CHS = adc_chn[adc_pin[adc_idx]];

            adc_status = ADC_CHARGE;
        }
    }
    else {

        // ADC 開始
        ADCON0bits.GO_nDONE = 1 ;

        adc_status = ADC_GO;
    }
    TMR1 = 65535-ADC_INTERVAL;
}

void init_adc(void)
{
    unsigned char porta = 0;
    unsigned char portb = 0;
    unsigned char portc = 0;

    adc_status = ADC_DISABLE;
    adc_idx = 0;
    adc_maxidx = 0;
    for( unsigned char i=0; i < ADC_MAXCH+1; ++i ) adc_value[i] = 0;
    
    unsigned char num = get_pinMode(ADC,&porta,&portb,&portc);
    if( num ) adc_status = ADC_GO;
    else return;
    
    adc_chn[PIN02_RA5] = 0b000101;
    adc_chn[PIN03_RA4] = 0b000100;
    // RA3 は MCLR/Vpp 固定
    adc_chn[PIN17_RA2] = 0b000010;
    // RA1 は ICSPCLK 固定
    // RA0 は ICSPDAT 固定

    adc_chn[PIN10_RB7] = 0b001111;
    adc_chn[PIN11_RB6] = 0b001110;
    adc_chn[PIN12_RB5] = 0b001101;
    adc_chn[PIN13_RB4] = 0b001100;

    adc_chn[PIN09_RC7] = 0b010111;
    adc_chn[PIN08_RC6] = 0b010110;
    adc_chn[PIN05_RC5] = 0b010101;
    adc_chn[PIN06_RC4] = 0b010100;
    adc_chn[PIN07_RC3] = 0b010011;
    adc_chn[PIN14_RC2] = 0b010010;
    adc_chn[PIN15_RC1] = 0b010001;
    adc_chn[PIN16_RC0] = 0b010000;
    
    if( porta & 0b00100000 ) adc_pin[adc_maxidx++] = PIN02_RA5;
    if( porta & 0b00010000 ) adc_pin[adc_maxidx++] = PIN03_RA4;
    // RA3 は MCLR/Vpp 固定
    if( porta & 0b00000100 ) adc_pin[adc_maxidx++] = PIN17_RA2;
    // RA1 は ICSPCLK 固定
    // RA0 は ICSPDAT 固定

    if( portb & 0b10000000 ) adc_pin[adc_maxidx++] = PIN10_RB7;
    if( portb & 0b01000000 ) adc_pin[adc_maxidx++] = PIN11_RB6;
    if( portb & 0b00100000 ) adc_pin[adc_maxidx++] = PIN12_RB5;
    if( portb & 0b00010000 ) adc_pin[adc_maxidx++] = PIN13_RB4;

    if( portc & 0b10000000 ) adc_pin[adc_maxidx++] = PIN09_RC7;
    if( portc & 0b01000000 ) adc_pin[adc_maxidx++] = PIN08_RC6;
    if( portc & 0b00100000 ) adc_pin[adc_maxidx++] = PIN05_RC5;
    if( portc & 0b00010000 ) adc_pin[adc_maxidx++] = PIN06_RC4;
    if( portc & 0b00001000 ) adc_pin[adc_maxidx++] = PIN07_RC3;
    if( portc & 0b00000100 ) adc_pin[adc_maxidx++] = PIN14_RC2;
    if( portc & 0b00000010 ) adc_pin[adc_maxidx++] = PIN15_RC1;
    if( portc & 0b00000001 ) adc_pin[adc_maxidx++] = PIN16_RC0;

    TRISA |=  porta;
    ANSELA |= porta;
    TRISB |=  portb;
    ANSELB |= portb;
    TRISC |=  portc;
    ANSELC |= portc;
    
    printf("-----\r\nADC:\r\n");
    printf("portA = 0x%x, portB = 0x%x, portC = 0x%x\r\n",porta,portb,portc);

    // 全割り込み処理不可
    INTCONbits.GIE = 0;

    ADRES = 0;
    
    // ADC 結果右詰め
    ADCON1bits.ADFM = 1;

    // ADC クロック設定
    // 早すぎると正しく変換できないので、238p 表22-1 で影が入ってないマス目のスピードを選ぶ
    ADCON1bits.ADCS = 0b001;  // FOSC=4MHzなので FOSC/8 を選択

    // ADC 割り込み不許可
    PIE1bits.ADIE = 0;
    
    // ADC 有効化
    ADCON0bits.ADON = 1;

    // タイマー1を使用
    // 4Mhz で駆動しているのでタイマーのカウントアップ間隔 = prescale*1/(FOSC/4) = 1/(4/4*10^6) = 1 マイクロ秒
    T1CONbits.TMR1CS = 0b00; // クロック : FOSC/4
    T1CONbits.T1CKPS = 0b00; // prescale : 1
    TMR1 = 65535-ADC_INTERVAL;
    PIR1bits.TMR1IF = 0; // タイマー 割り込みフラグリセット
    PIE1bits.TMR1IE = 1; // タイマー 割り込み許可
    T1CONbits.TMR1ON = 1; // タイマー 有効化

    // 周辺割り込み許可
    INTCONbits.PEIE = 1;
    
    // 全割り込み処理許可
    INTCONbits.GIE = 1; 
}
