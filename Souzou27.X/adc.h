#pragma once

enum
{
    ADC_MAXCH = 20,
    ADC_DISABLE = 255,
    ADC_CHARGE = 0,
    ADC_GO = 1,

    ADC_INTERVAL = 10000,  // サンプリング間隔(マイクロ秒)
};

void init_adc(void);
void adc_isr(void);

extern volatile unsigned short adc_value[ADC_MAXCH+1];;

#define ANA5 adc_value[PIN02_RA5]
#define ANA4 adc_value[PIN03_RA4]
#define ANA3 adc_value[PIN04_RA3]
#define ANA2 adc_value[PIN17_RA2]
#define ANA1 adc_value[PIN18_RA1]
#define ANA0 adc_value[PIN19_RA0]

#define ANB7 adc_value[PIN10_RB7]
#define ANB6 adc_value[PIN11_RB6]
#define ANB5 adc_value[PIN12_RB5]
#define ANB4 adc_value[PIN13_RB4]

#define ANC7 adc_value[PIN09_RC7]
#define ANC6 adc_value[PIN08_RC6]
#define ANC5 adc_value[PIN05_RC5]
#define ANC4 adc_value[PIN06_RC4]
#define ANC3 adc_value[PIN07_RC3]
#define ANC2 adc_value[PIN14_RC2]
#define ANC1 adc_value[PIN15_RC1]
#define ANC0 adc_value[PIN16_RC0]
