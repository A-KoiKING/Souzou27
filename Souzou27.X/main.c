#include "common.h"

void Servo(int angle);

void setup(void)
{
    // pinMode(ピン名称(または番号),モード)
    //
    // モード
    // OUTPUT  : ディジタル出力 (デフォルト)
    // INPUT   : ディジタル入力 (内部弱プルアップ 無効)
    // INPUT_PULLUP   : ディジタル入力 (内部弱プルアップ 有効)
    // ADC     : アナログ入力 (10 bit)
    // PWM1〜4 : パルス幅変調 (3系統同時出力可)
    // TX      : シリアル通信 送信 (115200ボー)
    // RX      : シリアル通信 受信 (115200ボー)
    pinMode(PIN03_RA4,PWM4);   //サーボモータ
    pinMode(PIN05_RC5,PWM1);   //モータ変速
    pinMode(PIN06_RC4,OUTPUT); //モータ制御
    pinMode(PIN07_RC3,OUTPUT); //モータ制御
    pinMode(PIN08_RC6,OUTPUT); //ウィンカー左
    pinMode(PIN09_RC7,OUTPUT); //LED（元ブザー）
    pinMode(PIN10_RB7,OUTPUT); //LED（ブレーキランプ）
    pinMode(PIN11_RB6,INPUT);  //ラインセンサ
    pinMode(PIN12_RB5,INPUT);  //ラインセンサ
    pinMode(PIN13_RB4,INPUT);  //ラインセンサ
    pinMode(PIN14_RC2,INPUT);  //測距センサ
    pinMode(PIN15_RC1,INPUT_PULLUP); //スタートスイッチ
    pinMode(PIN16_RC0,OUTPUT); //ウィンカー右
    // (補足) ピン番号を使って pinMode(16,OUTPUT); とすることも可能
    // (補足) OUTPUT はデフォルト動作なので省略可能
}


void run(void) 
{
    //ラインセンサ初期化
    RB4 = 1;
    RB5 = 1;
    RB6 = 0;
    
    //ボタンチェック
    if(RC1 == 0){
        while(1){
            //モータ初期化(前進)
            //pwm1();
            RC3 = 1;
            RC4 = 0;
            //壁を見つけたとき
            if(RC2 == 1){
                //モータ制御(ブレーキ)
                RC3 = 1;
                RC4 = 1;
                //ブレーキランプ
                RB7 = 1;
                break;
            //左折
            }else if(RB4 == 0 && RB5 == 1 && RB6 == 0){
                //サーボ左
                void Servo(-30);
                //左ウィンカー
                while(RB4 == 0){
                    RC6 = 1;
                    __delay_ms(500);
                    RC6 = 0;
                    __delay_ms(500);
                }
            //右折
            }else if(RB4 == 1 && RB5 == 0 && RB6 == 0){
                //サーボ右
                void Servo(30);
                //右ウィンカー
                while(RB5 == 0){
                    RC0 = 1;
                    __delay_ms(500);
                    RC0 = 0;
                    __delay_ms(500);
                }
            //後退
            }else if(RB4 == 1 && RB5 == 1 && RB6 == 1){
                //モータ制御(後退)
                //pwm1();
                RC3 = 0;
                RC4 = 1;
            }
        }
    }
    return;
}


void Servo(int angle)
{
    if(angle <= -91 || angle >= 91) return;
    float value = 1500+(angle/0.09);
    pwm4(20000,value);
    return;
}


/*
//測距センサ＆ブレーキランプ
void run(void)
{
    while(1)
    {
        if(RC2 == 1)
        {
            RB7 = 1;
        }
    }
    
    return;
}
*/

/*
//サーボ＆スタートボタン
void run(void)
{
    RA4 = 1;
    while(1)
    {
        if(RC1 == 0)
        {
            pwm4(20000,500);
            RB7 = 1;
        }
        else
        {
            pwm4(20000,2500);
            RB7 = 0;
        }
    }
    return;
}
*/