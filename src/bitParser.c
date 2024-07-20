
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "bys.h"
#include "bitParser.h"

void bp_stringTobit(BitUint_t *dst, BlockStringify_t stringify)
{
    *dst = 0b0;
    char n = *stringify;
    while (n)
    {
        *dst <<= 1;
        *dst |= (n == Blockn2cOffset ? 0 : 1);
        n = *(++stringify);
    }
}
void bp_bitToString(BlockStringify_t *dst, size_t dstSize, BitUint_t bit)
{
    BitUint_t binMask = 0b1;
    // -2 one is self,one is \0
    char *cLast = *dst + dstSize - 2;
    for (int i = 0; i < dstSize; i++)
    {
        if (bit)
        {
            *(cLast - i) = (char)(binMask & bit) | Blockn2cOffset;
            bit >>= 1;
        }
        else
        {
            *(cLast - i) = (char)Blockn2cOffset;
        }
    }
    // NULL
    *(cLast + 1) = '\0';
}

void bp_arrayToStringify(BlockStringify_t *dst, size_t dstSize, Block_t *arr, size_t arrSize)
{
    char *c = *dst;
    int j = 0;
    for (int i = 0; i < dstSize; i++)
    {
        *(c + i) = (dstSize - i > arrSize ? Blockn2cOffset : arr[j++] | Blockn2cOffset);
    }
    *(c + dstSize) = '\0';
}

bool bp_bitwiseHaveTrueBit(BitUint_t bit)
{
    for (; bit; bit >>= 1)
    {
        if (bit & 1)
        {
            return true;
        }
    }
    return false;
}