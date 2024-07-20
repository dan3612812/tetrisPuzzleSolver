
#include <stdlib.h>
#include "map.h"
#include "puzzle.h"
#include "agent.h"

AgentFun_t agent_init(Agent_t *agent, Map_t *map, Puzzle_t *puzzleArray, uint8_t puzzleCount)
{
    agent = malloc(sizeof(Agent_t));
    if (agent == NULL)
    {
        return AgentFunFail;
    }
    agent->originMapStringify = malloc(strlen(map->stringify) + 1);
    if (agent->originMapStringify == NULL)
    {
        goto _free_agent;
    }
    memcpy(agent->originMapStringify, map->stringify, strlen(map->stringify) + 1);
    agent->map = map;
    agent->puzzleArray = puzzleArray;
    agent->puzzleCount = puzzleCount;

    return AgentFunOk;

_free_agent:
    free(agent);
}
// ap="012345" or "543021"
Agent_t agent_verificationPermutation(Agent_t *agent, AgentPermutation_t ap)
{
    for (int i = 0; i < agent->puzzleCount; i++)
    {
    }
}

// AgentFun_t agent_working(Agent_t *agent)
// {
// }