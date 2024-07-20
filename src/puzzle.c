#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "puzzle.h"

/**
 * @deprecated
 * @brief
 *
 * @param arrStrPtr
 * @param stringify
 * @param arrayCount
 * @return PuzzleFun_t
 */
PuzzleFun_t puzzle_array_stringify(PuzzleStringify_t *arrStrPtr, Block_t *stringify, size_t arrayCount)
{
    *arrStrPtr = malloc(arrayCount);
    if (arrStrPtr == NULL)
    {
        return PuzzleFunFail;
    }
    char *temp = malloc(sizeof(char) * (arrayCount + 1));
    if (temp == NULL)
    {
        goto _free_arrStrPtr;
    }
    for (int i = 0; i < arrayCount; i++)
    {
        temp[i] = stringify[i] + Blockn2cOffset; // ascii 0 => '0'
    }
    temp[arrayCount] = '\0';
    *arrStrPtr = temp;
    return PuzzleFunOk;

_free_arrStrPtr:
    free(arrStrPtr);
    return PuzzleFunFail;
}

PuzzleFun_t puzzle_init(Puzzle_t **puzzle, PuzzleBasicUnit_t width, PuzzleBasicUnit_t high, PuzzleStringify_t stringify)
{
    if ((width * high) != strlen(stringify))
    {
        return PuzzleFunInitPropertyFail;
    }
    Puzzle_t *tempPuzzle = malloc(sizeof(Puzzle_t));
    if (tempPuzzle == NULL)
    {
        return PuzzleFunFail;
    }
    PuzzleStringify_t *tempStringify = malloc(strlen(stringify) + 1);
    if (tempStringify == NULL)
    {
        goto _free_Puzzle;
    }
    memcpy(tempStringify, stringify, strlen(stringify) + 1);
    tempPuzzle->high = high;
    tempPuzzle->width = width;
    tempPuzzle->stringify = (PuzzleStringify_t)tempStringify;
    *puzzle = tempPuzzle;
    return PuzzleFunOk;

_free_Puzzle:
    free(tempPuzzle);
    return PuzzleFunFail;
}
PuzzleFun_t puzzle_clockwiseRotation(Puzzle_t *puzzle)
{
    PuzzleStringify_t tmpStr = malloc(strlen(puzzle->stringify));
    if (tmpStr == NULL)
    {
        return PuzzleFunFail;
    }
    memcpy(tmpStr, puzzle->stringify, strlen(puzzle->stringify) + 1);
    const PuzzleBasicUnit_t high = puzzle->high;
    const PuzzleBasicUnit_t width = puzzle->width;
    for (int i = 0; i < strlen(puzzle->stringify); i++)
    {
        size_t newIndex = (i / high) + (high - 1 - i % high) * width;
        puzzle->stringify[i] = (char)tmpStr[newIndex];
    }

    PuzzleBasicUnit_t temp = puzzle->width;
    puzzle->width = puzzle->high;
    puzzle->high = temp;
    return PuzzleFunOk;
}
PuzzleFun_t puzzle_free(Puzzle_t *puzzle)
{
    if (puzzle == NULL)
    {
        return PuzzleFunFail;
    }
    if (puzzle->stringify)
    {
        free(puzzle->stringify);
    }
    puzzle->stringify = NULL;
    free(puzzle);
    return PuzzleFunOk;
}

void puzzle_prints(Puzzle_t *puzzle)
{
    printf("The Puzzle\n\twidth:%d\n\thigh:%d\n\tarrStr:%s\n", puzzle->width, puzzle->high, puzzle->stringify);
};
void puzzle_printg(Puzzle_t *puzzle)
{
    // static const unsigned short space = 32;
    for (int i = 0; i < strlen(puzzle->stringify); i++)
    {
        printf("%s", puzzle->stringify[i] - Blockn2cOffset == 0 ? " " : "▮");

        if (0 == (i + 1) % puzzle->width)
        {
            printf("\n");
        }
    }
}
