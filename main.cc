// Arquivo: main.cc
// Autor: Arliones Hoeller, IFSC-SJE

#include <stdio.h>
#include "uart.h"
#include "adc.h"


Uart uart(Uart::UART_9600);
ADC adc(ADC::ADC_CH0);
char medicao [64];

void setup()
{
    __asm__ ("sei");
    uart.puts("setup\n");
}

void busy_wait_delay(int times)
{
    while (times--)
    {
        unsigned long x = 0x7ffff;
        while(x--) __asm__ ("nop");
    }
}

void loop()
{
    
    int media = 0;
    for (int i = 0; i < 16; i++)
    {
        media = media + adc.get(i);
    }
    media = media /16;
    sprintf(medicao, "Resultado da Leitura ADC: %d \n", media);
    uart.puts(medicao);
    busy_wait_delay(2);
}

int main()
{
    setup();
    while (true)
    {
        loop();
    }
}
