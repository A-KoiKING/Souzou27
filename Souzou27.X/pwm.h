#pragma once

enum
{
    PWM_NUM = 4,
    
    PWM_DISABLE = 0,
    PWM_ENABLE = 1,
    
    PWM_DEFAULT_PERIOD = 15000, // デフォルト周期(マイクロ秒)
    PWM_DEFAULT_WIDTH = 5000 // デフォルト幅(マイクロ秒)
};

void init_pwm(void);
void pwm1(const unsigned short period, const unsigned short width);
void pwm2(const unsigned short period, const unsigned short width);
void pwm3(const unsigned short period, const unsigned short width);
void pwm4(const unsigned short period, const unsigned short width);
