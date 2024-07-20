#ifndef _BYS_AGENT_H_
#define _BYS_AGENT_H_
#include <stdlib.h>
#include "map.h"
#include "puzzle.h"

typedef struct
{
    Map_t *map;
    MapStringify_t originMapStringify;
    Puzzle_t *puzzleArray;
    uint8_t puzzleCount;
    uint8_t puzzleIndex;
} Agent_t;

typedef enum
{
    AgentFunOk = FunOk,
    AgentFunFail = FunFail,
} AgentFun_t;
typedef char *AgentPermutation_t;

AgentFun_t agent_init(Agent_t *agent, Map_t *map, Puzzle_t *puzzleArray, uint8_t puzzleCount);
#endif