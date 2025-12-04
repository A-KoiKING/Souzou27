#pragma once

void init_pinMode(void);
void pinMode(const unsigned char pinno, const unsigned char mode);
unsigned char get_pinMode(unsigned char type, unsigned char* const porta,unsigned char* const portb, unsigned char* const portc);
