#include <stdio.h>

#include "map.h"
#include "puzzle.h"
#include "agent.h"

// TODO: support the multiple process
// TODO: support the turning the puzzle clockwise option
void testGameA()
{
    // TODO: dynamic load the map
    Map_t *map = NULL;
    map_init(&map, 3, 3, "000000000");
    size_t puzzleCount = 3;
    PuzzleArray_t *parr = NULL;
    // TODO: dynamic load the puzzles
    puzzle_arrayInit(&parr, puzzleCount);
    puzzle_init(&parr[0], 2, 3, "101011");
    puzzle_init(&parr[1], 2, 2, "1110");
    puzzle_init(&parr[2], 1, 2, "11");
    // TODO: auto generate the permutation
    AgentPermutation_t ap = malloc(sizeof(uint8_t) * puzzleCount);
    // ap[0] = 2, ap[1] = 1, ap[2] = 0; // fail
    ap[0] = 0, ap[1] = 1, ap[2] = 2; // success
    Agent_t *agent = NULL;
    agent_init(&agent, map, parr, puzzleCount);
    if (agent_verificationPermutation(agent, ap, puzzleCount) == AgentFunOk)
    {
        agent_printAnswer(agent, ap, puzzleCount);
    }
}
void testGameB(void)
{
    // FIXME: check it the putPuzzle have bug!!!
    Map_t *map = NULL;
    map_init(&map, 7, 5, "00000000000000000100000000000000000");
    size_t puzzleCount = 8;
    PuzzleArray_t *parr = NULL;
    puzzle_arrayInit(&parr, puzzleCount);
    puzzle_init(&parr[0], 3, 3, "100100111");
    puzzle_init(&parr[1], 4, 2, "11110001");
    puzzle_init(&parr[2], 2, 3, "111110");
    puzzle_init(&parr[3], 3, 1, "111");
    puzzle_init(&parr[4], 2, 3, "101110");
    puzzle_init(&parr[5], 2, 3, "010111");
    puzzle_init(&parr[6], 3, 2, "111110");
    puzzle_init(&parr[7], 2, 2, "0111");
    AgentPermutation_t ap = malloc(sizeof(uint8_t) * puzzleCount);
    ap[0] = 0, ap[1] = 1, ap[2] = 2, ap[3] = 3, ap[4] = 4, ap[5] = 5, ap[6] = 6, ap[7] = 7;
    Agent_t *agent = NULL;
    agent_init(&agent, map, parr, puzzleCount);
    if (agent_verificationPermutation(agent, ap, puzzleCount) == AgentFunOk)
    {
        agent_printAnswer(agent, ap, puzzleCount);
    }
    else
    {
        printf("FIALED\n");
    }
}

int main(void)
{
    testGameA();
    // testGameB();
    return 0;
}