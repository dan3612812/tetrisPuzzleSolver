#ifndef _BYS_PUZZLE_H_
#define _BYS_PUZZLE_H_

#include "bys.h"
typedef unsigned short PuzzleBasicUnit_t;
typedef char *PuzzleStringify_t;
/**
 * @brief The Puzzle_t struct
 * @details Use the Quadrant4 (+x,-y)
 */
typedef struct
{
    PuzzleBasicUnit_t width;     /**< The puzzle width is horizontal line, the value is |x| */
    PuzzleBasicUnit_t high;      /**< The puzzle high is vertical line, the value is |y| */
    PuzzleStringify_t stringify; /**< Express the puzzle with 1d-stringify, the size is (x*y) */
} Puzzle_t;

typedef Puzzle_t *PuzzleArray_t;

typedef enum
{
    PuzzleFunOk = FunOk,
    PuzzleFunFail = FunFail,
    PuzzleFunInitPropertyFail = 2,
} PuzzleFun_t;
PuzzleFun_t puzzle_arrayInit(PuzzleArray_t **puzzleArray, size_t puzzleArrayCount);
PuzzleFun_t puzzle_init(Puzzle_t **puzzle, PuzzleBasicUnit_t width, PuzzleBasicUnit_t high, PuzzleStringify_t stringify);
PuzzleFun_t puzzle_clockwiseRotation(Puzzle_t *puzzle);
PuzzleFun_t puzzle_free(Puzzle_t *puzzle);
void puzzle_prints(Puzzle_t *puzzle);
void puzzle_printg(Puzzle_t *puzzle);
#endif