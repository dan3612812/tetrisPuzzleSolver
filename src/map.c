#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "map.h"
#include "puzzle.h"
#include "bitParser.h"

MapFun_t map_init(Map_t **map, MapBasicUnit_t width, MapBasicUnit_t high, MapStringify_t stringify)
{
    if (strlen(stringify) != high * width)
    {
        return MapFunInitPropertyFail;
    }
    *map = malloc(sizeof(Map_t));
    if (*map == NULL)
    {
        return MapFunFail;
    }
    (**map).stringify = malloc(width * high + 1);
    if ((**map).stringify == NULL)
    {
        goto _free_map;
    }
    memcpy((**map).stringify, stringify, strlen(stringify) + 1);
    (**map).high = high;
    (**map).width = width;
    return MapFunOk;

_free_map:
    free(*map);

    return MapFunFail;
}
MapFun_t map_putPuzzle(Map_t *map, Puzzle_t *puzzle, size_t offset)
{
    MapFun_t result = map_tryPutPuzzle(map, puzzle, offset);
    if (result != MapFunOk)
    {
        return result;
    }
    size_t paddingPuzzleLength = puzzle->high * map->width;
    size_t offsetRemainder = offset % map->width;
    int puzzleIndex = 0;

    for (int i = 0; i < paddingPuzzleLength; i++)
    {
        int iRemainder = i % map->width;
        // when the iRemainder not in the
        // `puzzle left padding` && `the puzzle right padding`
        if (iRemainder >= offsetRemainder && iRemainder + 1 <= puzzle->width + offsetRemainder)
        {
            int mapIndexOffset = i + (offset / map->width) * map->width;
            // assign puzzle value to map
            map->stringify[mapIndexOffset] = puzzle->stringify[puzzleIndex++];
        }
    }
    return MapFunOk;
}

MapFun_t map_tryPutPuzzle(Map_t *map, Puzzle_t *puzzle, size_t offset)
{
    if (puzzle->width > map->width)
    {
        return MapFunOverPuzzleWidth;
    }
    if (puzzle->high > map->high)
    {
        return MapFunOverPuzzleHigh;
    }
    if (strlen(map->stringify) <= offset)
    {
        return MapFunOverOffset;
    }
    size_t offsetWidth = offset % map->width;
    size_t offsetHight = offset / map->width;
    if (offsetWidth + puzzle->width > map->width)
    {
        return MapFunOverOffsetWidth;
    }
    if (offsetHight + puzzle->high > map->high)
    {
        return MapFunOverOffsetHigh;
    }
    // get the part of map
    MapStringify_t partOfMap = malloc(strlen(puzzle->stringify));
    for (int i = 0; i < strlen(puzzle->stringify); i++)
    {
        size_t positionIndex = offsetWidth + (i % puzzle->width) + (((i / puzzle->width) + offsetHight) * map->width);
        partOfMap[i] = map->stringify[positionIndex];
    }
    // check the puzzle can into the partOfMap
    BitUint_t p, m;
    bp_stringTobit(&p, puzzle->stringify);
    bp_stringTobit(&m, partOfMap);
    if (bp_bitwiseHaveTrueBit(p & m))
    {
        // true mean collision
        return MapFunFail;
    };

    return MapFunOk;
}
MapFun_t map_deepCopy(Map_t **dstMap, Map_t *srcMap)
{
    if (srcMap == NULL)
    {
        return MapFunFail;
    }
    if (*dstMap != NULL)
    {
        return MapFunFail;
    }
    *dstMap = malloc(sizeof(Map_t));
    if (dstMap == NULL)
    {
        return MapFunFail;
    }
    (**dstMap).stringify = malloc(strlen(srcMap->stringify) + 1);
    if ((**dstMap).stringify == NULL)
    {
        goto _free_dstMap;
    }
    memcpy((**dstMap).stringify, srcMap->stringify, strlen(srcMap->stringify) + 1);
    (**dstMap).high = srcMap->high;
    (**dstMap).width = srcMap->width;

    return MapFunOk;

_free_dstMap:
    free(*dstMap);
    return MapFunFail;
}
bool map_isFull(Map_t *map)
{
    for (int i = 0; i < strlen(map->stringify); i++)
    {
        if (map->stringify[i] == Blockn2cOffset)
        {
            return false;
        }
    }
    return true;
}

void map_prints(Map_t *map)
{
    printf("The Map:\n\twidth:%d\n\thigh:%d\n\tstringify:%s\n", map->width, map->high, map->stringify);
}
void map_printg(Map_t *map)
{
    // static const unsigned short space = 32;
    for (int i = 0; i < strlen(map->stringify); i++)
    {
        if (i % map->width == 0)
        {
            printf("[%02d](%04d):", (i / map->width) + 1, i);
        }
        printf("%s", map->stringify[i] - Blockn2cOffset == 0 ? "□" : "■");

        if (0 == (i + 1) % map->width)
        {
            printf("\n");
        }
    }
}
