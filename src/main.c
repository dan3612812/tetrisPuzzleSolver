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
    Map_t *map = NULL;
    map_init(&map, 7, 5, "00000000000000000100000000000000000");
    size_t puzzleCount = 8;
    PuzzleArray_t *parr = NULL;
    puzzle_arrayInit(&parr, puzzleCount);
    puzzle_init(&parr[0], 3, 3, "100100111");
    puzzle_init(&parr[1], 2, 3, "111110");
    puzzle_init(&parr[2], 4, 2, "11110001");
    puzzle_init(&parr[3], 3, 1, "111");
    puzzle_init(&parr[4], 2, 3, "010111");
    puzzle_init(&parr[5], 2, 3, "101110");
    puzzle_init(&parr[6], 2, 2, "0111");
    puzzle_init(&parr[7], 3, 2, "111110");
    Agent_t *agent = NULL;
    agent_init(&agent, map, parr, puzzleCount);
    if (agent_auto(agent, puzzleCount) != AgentFunOk)
    {
        printf("Failed\n");
    }
}
void testGameC(void)
{
    Map_t *map = NULL;
    map_init(&map, 15, 8, "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    size_t puzzleCount = 22;
    PuzzleArray_t *parr = NULL;
    puzzle_arrayInit(&parr, puzzleCount);
    // puzzle_init(&parr[0], 3, 3, "100100111");
    // puzzle_init(&parr[1], 4, 2, "11111000");
    // puzzle_init(&parr[2], 3, 3, "010111010");
    // puzzle_init(&parr[3], 4, 2, "11110100");
    // puzzle_init(&parr[4], 3, 4, "011010110100");
    // puzzle_init(&parr[5], 4, 3, "011111001000");
    // puzzle_init(&parr[6], 2, 3, "110111");
    // puzzle_init(&parr[7], 3, 3, "011010110");
    // puzzle_init(&parr[8], 3, 3, "011111010");
    // puzzle_init(&parr[9], 3, 4, "010010111010");
    // puzzle_init(&parr[10], 3, 3, "011110010");
    // puzzle_init(&parr[11], 3, 3, "110111110");
    // puzzle_init(&parr[12], 3, 3, "111100110");
    // puzzle_init(&parr[13], 4, 3, "000111110001");
    // puzzle_init(&parr[14], 3, 3, "001111010");
    // puzzle_init(&parr[15], 2, 3, "111010");
    // puzzle_init(&parr[16], 3, 3, "001111110");
    // puzzle_init(&parr[17], 3, 3, "010011111");
    // puzzle_init(&parr[18], 3, 3, "100111100");
    // puzzle_init(&parr[19], 3, 3, "001001111");
    // puzzle_init(&parr[20], 2, 3, "101111");
    // puzzle_init(&parr[21], 4, 2, "10101111");
    puzzle_init(&parr[0], 4, 2, "11110100");
    puzzle_init(&parr[1], 3, 3, "011110010");
    puzzle_init(&parr[2], 3, 3, "010111010");
    puzzle_init(&parr[3], 2, 3, "110111");
    puzzle_init(&parr[4], 3, 4, "011010110100");
    puzzle_init(&parr[5], 3, 3, "100100111");
    puzzle_init(&parr[6], 4, 3, "011111001000");
    puzzle_init(&parr[7], 3, 3, "011010110");
    puzzle_init(&parr[8], 3, 3, "011111010");
    puzzle_init(&parr[9], 4, 2, "11111000");
    puzzle_init(&parr[10], 2, 3, "111010");
    puzzle_init(&parr[11], 3, 3, "100111100");
    puzzle_init(&parr[12], 3, 3, "111100110");
    puzzle_init(&parr[13], 3, 4, "010010111010");
    puzzle_init(&parr[14], 4, 2, "10101111");
    puzzle_init(&parr[15], 3, 3, "001111010");
    puzzle_init(&parr[16], 3, 3, "001111110");
    puzzle_init(&parr[17], 3, 3, "110111110");
    puzzle_init(&parr[18], 2, 3, "101111");
    puzzle_init(&parr[19], 4, 3, "000111110001");
    puzzle_init(&parr[20], 3, 3, "010011111");
    puzzle_init(&parr[21], 3, 3, "001001111");
    Agent_t *agent = NULL;
    agent_init(&agent, map, parr, puzzleCount);
    if (agent_auto(agent, puzzleCount) != AgentFunOk)
    {
        printf("Failed\n");
    }
}

int main(void)
{
    // testGameA();
    // testGameB();
    testGameC();
    return 0;
}