#include "common.h"

void Servo(float angle);

//// タイマー1のISR
//void isr_timer1(void)
//{
//    count1++;
//}

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
    pinMode(PIN11_RB6,INPUT);  //ラインセンサ後
    pinMode(PIN12_RB5,INPUT);  //ラインセンサ
    pinMode(PIN13_RB4,INPUT);  //ラインセンサ
    pinMode(PIN14_RC2,ADC);  //測距センサ
    pinMode(PIN15_RC1,INPUT_PULLUP); //スタートスイッチ
    pinMode(PIN16_RC0,OUTPUT); //ウィンカー右
    // (補足) ピン番号を使って pinMode(16,OUTPUT); とすることも可能
    // (補足) OUTPUT はデフォルト動作なので省略可能
    
//    // 割り込み間隔設定 (マイクロ秒、最大 524280)
//    timer1(100000);
//    
//    // 引数: ISRのアドレス設定
//    config_timer1(isr_timer1);
}

void run(void) 
{   
    //右
    if(RB4 == 1){
        RC0 = 1;
    }
    else{
        RC0 = 0;
    }
    //左
    if(RB5 == 1){
        RC6 = 1;
    }
    else{
        RC6 = 0;
    }
    //中央
    if(RB6 == 1){
        RB7 = 1;
    }
    else{
        RB7 = 0;
    }
    
    //ボタンチェック
    if(RC1 == 0){
        //角度保存
        int PreSta = 0;
        //サーボ角度リセット
        Servo(0);
        //ブレーキランプOFF
        RB7 = 0;
        //ウィンカー消灯
        RC0 = 0;
        RC6 = 0;
        //モータ初期化(前進)
        pwm1(16000,14000);
        //前進
        RC3 = 0;
        RC4 = 1;
        //状態保存
        PreSta = 0;
        
        while(1){
            //壁を見つけたとき
            if(ANC2 >= 700){
                //モータ制御(ブレーキ)
                RC3 = 1;
                RC4 = 1;
                //ブレーキランプON
                RB7 = 1;
                //サーボ角度リセット
                Servo(0);
                //ウィンカー点灯
                RC0 = 1;
                RC6 = 1;
                break;
            //前進
            }else if(RB4 == 0 && RB5 == 0 && RB6 == 0){
                //サーボ前
                Servo(0);
                //前進
                RC3 = 0;
                RC4 = 1;
                //状態保存       
                PreSta = 0;
                //ウィンカー消灯
                RC0 = 0;
                RC6 = 0;
            //左折
            }else if(RB4 == 0 && RB5 == 1 && RB6 == 0){
                //サーボ左
                Servo(25);
                //前進
                RC3 = 0;
                RC4 = 1;
                //状態保存
                PreSta = 1;
                //左ウィンカー
                RC0 = 0;
                RC6 = 1;
            //大きく左折
            }else if(RB4 == 0 && RB5 == 1 && RB6 == 1){
                //サーボ左
                Servo(30);
                //前進
                RC3 = 0;
                RC4 = 1;
                //状態保存
                PreSta = 1;
                //左ウィンカー
                RC0 = 0;
                RC6 = 1;
            //右折
            }else if(RB4 == 1 && RB5 == 0 && RB6 == 0){
                //サーボ右
                Servo(-25);
                //前進
                RC3 = 0;
                RC4 = 1;
                //状態保存                      
                PreSta = 2;
                //右ウィンカー
                RC0 = 1;
                RC6 = 0;
            //大きく右折
            }else if(RB4 == 1 && RB5 == 0 && RB6 == 1){
                //サーボ右
                Servo(-30);
                //前進
                RC3 = 0;
                RC4 = 1;
                //状態保存
                PreSta = 2;
                //右ウィンカー
                RC0 = 1;
                RC6 = 0;
            //後退
            }else if(RB4 == 1 && RB5 == 1 && RB6 == 1){
                //モータ制御(後退)
                RC3 = 1;
                RC4 = 0;
//                //モータ後進
//                pwm1(16000,10000);
                do{
                    switch(PreSta){
                        case 0:
                            Servo(0);
                            RC0 = 0;
                            RC6 = 0;                            
                            break;
                        case 1:
                            Servo(-20);
                            //左ウィンカー
                            RC0 = 0;
                            RC6 = 1;
                            break;
                        case 2:
                            Servo(20);
                            //右ウィンカー
                            RC0 = 1;
                            RC6 = 0;
                            break;
                    }
                    __delay_ms(500);
                }while(RB4 == 1 && RB5 == 1 && RB6 == 1);
//                //モータ速度(前進)
//                pwm1(16000,14000);
            }
        }
    }
    return;
}

void Servo(float angle)
{
    if(angle < -90 || angle > 90) return;
    int value = (int)(1500 + angle * 100 / 9.0f);
    pwm4(20000,(unsigned short)value);
    return; 
}

/*
//ラインセンサ確認コード
void run(void){
    Servo(0);
    //右
    if(RB4 == 1){
        RC0 = 1;
    }
    else{
        RC0 = 0;
    }
    //左
    if(RB5 == 1){
        RC6 = 1;
    }
    else{
        RC6 = 0;
    }
    //中央
    if(RB6 == 1){
        RB7 = 1;
    }
    else{
        RB7 = 0;
    }
}
*/

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