#ifndef _BYS_MAP_H_
#define _BYS_MAP_H_
#include "bys.h"
#include "puzzle.h"
typedef unsigned short MapBasicUnit_t;
typedef char *MapStringify_t;
typedef struct
{
    MapBasicUnit_t width;     /**< The Map wdith */
    MapBasicUnit_t high;      /**< The Map hgih */
    MapStringify_t stringify; /** Express the Map with 1d-array */
} Map_t;

typedef enum
{
    MapFunOk = FunOk,
    MapFunFail = FunFail,
    MapFunInitPropertyFail = 2,
    MapFunOverOffset = 3,
    MapFunOverOffsetWidth = 4,
    MapFunOverOffsetHigh = 5,
    MapFunOverPuzzleWidth = 6,
    MapFunOverPuzzleHigh = 7,
} MapFun_t;

MapFun_t map_init(Map_t **map, MapBasicUnit_t width, MapBasicUnit_t high, MapStringify_t stringify);
MapFun_t map_putPuzzle(Map_t *map, Puzzle_t *puzzle, size_t offset);
MapFun_t map_tryPutPuzzle(Map_t *map, Puzzle_t *puzzle, size_t offset);
MapFun_t map_deepCopy(Map_t **dstMap, Map_t *srcMap);
void map_prints(Map_t *map);
void map_printg(Map_t *map);
#endif