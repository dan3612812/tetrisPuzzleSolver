#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>

#define count 1000000000

void ta(void)
{
    uint64_t a = 0b0000000000000000000000000000000000000000000000000000000000000000;
    uint64_t b = 0b1111111111111111111111111111111111111111111111111111111111111111;
    uint64_t c;
    for (int i = 0; i < count; i++)
    {
        c = a | b;
    }
}
void tb(void)
{
    uint8_t a = 0b00000000;
    uint8_t b = 0b11111111;
    uint8_t c;
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            c = a | b;
        }
    }
}

void tc(void)
{
    uint32_t a = 0b00000000000000000000000000000000;
    uint32_t b = 0b11111111111111111111111111111111;
    uint32_t c;
    for (int i = 0; i < count; i++)
    {
        c = a | b;
    }
}
