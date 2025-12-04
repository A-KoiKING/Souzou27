#pragma once

#include <stdio.h>

enum
{
    TX_DISABLE = 0,
    TX_ENABLE = 1,

    RX_DISABLE = 0,
    RX_ENABLE = 1,
};

void init_uart(void);
void putch(char data);
int getch(void);
