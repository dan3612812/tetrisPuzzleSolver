#ifndef _BYS_AGENT_H_
#define _BYS_AGENT_H_
#include <stdlib.h>
#include "map.h"
#include "puzzle.h"

typedef struct
{
    Map_t *map;
    MapStringify_t originMapStringify;
    PuzzleArray_t *puzzleArray;
    uint8_t puzzleCount;
    uint8_t *offsetArray;
} Agent_t;

typedef enum
{
    AgentFunOk = FunOk,
    AgentFunFail = FunFail,
    AgentFunArgumentFail = 2,
} AgentFun_t;
typedef uint8_t *AgentPermutation_t;

AgentFun_t agent_init(Agent_t **agent, Map_t *map, PuzzleArray_t *puzzleArray, uint8_t puzzleCount);
AgentFun_t agent_verificationPermutation(Agent_t *agent, AgentPermutation_t permutation, uint8_t permutationCount);
AgentFun_t agent_printAnswer(Agent_t *agent, AgentPermutation_t permutation, uint8_t permutationCount);
#endif