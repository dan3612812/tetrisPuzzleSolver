#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "puzzle.h"
#include "bitParser.h"
void gameA(void)
{
    // the map
    Map_t *map = NULL;
    map_init(&map, 6, 4, "000000000000000000000000");
    map_printg(map);
    // the puzzle
    Puzzle_t *pa, *pb, *pc, *pd, *pe, *pf;
    puzzle_init(&pa, 2, 3, "101101");
    puzzle_init(&pb, 3, 2, "110011");
    puzzle_init(&pc, 3, 2, "111010");
    puzzle_init(&pd, 3, 2, "100111");
    puzzle_init(&pe, 3, 2, "111010");
    puzzle_init(&pf, 2, 3, "010111");
    puzzle_prints(pa);
    printf("PutResult:%d\n", map_putPuzzle(map, pa, 4));
    map_printg(map);
}

void testA(void)
{
    Map_t *srcMap = NULL, *dstMap = NULL;
    map_init(&srcMap, 2, 2, "0101");
    printf("%d\n", map_deepCopy(&dstMap, srcMap));
}

int main(void)
{
    Map_t *map = NULL;
    map_init(&map, 3, 3, "000000000");
    Puzzle_t *parr[3];
    puzzle_init(&parr[0], 2, 3, "101011");
    puzzle_init(&parr[1], 2, 2, "1110");
    puzzle_init(&parr[2], 1, 2, "11");
    printf("%ld\n", sizeof(parr) / sizeof(parr[0]));
    for (int i = 0; i < 3; i++)
    {
        puzzle_printg(parr[i]);
        printf("========\n");
    }

    return 0;
}