
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "puzzle.h"
#include "agent.h"

AgentFun_t agent_init(Agent_t **agent, Map_t *map, PuzzleArray_t *puzzleArray, uint8_t puzzleCount)
{
    if (*agent != NULL)
    {
        return AgentFunFail;
    }
    Agent_t *tmpAgent = malloc(sizeof(Agent_t));
    if (tmpAgent == NULL)
    {
        return AgentFunFail;
    }
    tmpAgent->originMapStringify = malloc(strlen(map->stringify) + 1);
    if (tmpAgent->originMapStringify == NULL)
    {
        goto _free_agent;
    }
    memcpy(tmpAgent->originMapStringify, map->stringify, strlen(map->stringify) + 1);
    tmpAgent->map = map;
    tmpAgent->puzzleArray = puzzleArray;
    tmpAgent->puzzleCount = puzzleCount;
    *agent = tmpAgent;

    return AgentFunOk;

_free_agent:
    free(agent);
    return AgentFunFail;
}
// ap="{0,1,2,3,4,5} or {1,3,5,2,0,4}
AgentFun_t agent_verificationPermutation(Agent_t *agent, AgentPermutation_t permutation, uint8_t permutationCount)
{

    if (agent->puzzleCount != permutationCount)
    {
        return AgentFunArgumentFail;
    }
    PuzzleArray_t *pa = agent->puzzleArray;
    Map_t *map = agent->map;
    for (int i = 0; i < permutationCount; i++)
    {
        Puzzle_t *nowPuzzle = pa[permutation[i]];
        for (int j = 0; j < strlen(agent->originMapStringify); j++)
        {
            if (map_putPuzzle(map, nowPuzzle, j) == MapFunOk)
            {
                // DEBUG usage
                // map_printg(map);
                // printf("-------------[%d]\n", j);
                break;
            }
        }
    }

    AgentFun_t agentResult = map_isFull(map) ? AgentFunOk : AgentFunFail;
    // reset the puzzle.stringify.
    memcpy(map->stringify, agent->originMapStringify, strlen(map->stringify) + 1);
    return agentResult;
}

AgentFun_t agent_printAnswer(Agent_t *agent, AgentPermutation_t permutation, uint8_t permutationCount)
{
    if (agent->puzzleCount != permutationCount)
    {
        return AgentFunArgumentFail;
    }
    PuzzleArray_t *pa = agent->puzzleArray;
    Map_t *map = agent->map;
    size_t mapStringifyLen = strlen(map->stringify);
    MapStringify_t answer = malloc(mapStringifyLen + 1);
    answer[mapStringifyLen + 1] = '\0';
    // for each the block of map answer
    for (int i = 0; i < mapStringifyLen; i++)
    {
        answer[i] = map->stringify[i] == Blockn2cOffset + BlockFILL ? '@' : map->stringify[i];
    }
    // for each the puzzle the order by permutation
    for (int i = 0; i < permutationCount; i++)
    {
        Puzzle_t *nowPuzzle = pa[permutation[i]];
        // for each the map block
        for (int j = 0; j < strlen(agent->originMapStringify); j++)
        {
            if (map_putPuzzle(map, nowPuzzle, j) == MapFunOk)
            {
                // for each the puzzle of map , change the char that start of 'A'
                for (int k = 0; k < strlen(map->stringify); k++)
                {
                    if (map->stringify[k] == Blockn2cOffset + 1 && answer[k] == Blockn2cOffset)
                    {
                        answer[k] = 65 + i;
                    }
                }
                break;
            }
        }
    }
    // print the answer
    printf("Answer:\n");
    for (int i = 0; i < mapStringifyLen; i++)
    {
        if (i % map->width == 0)
        {
            printf("\t");
        }
        printf("%c", answer[i]);
        if ((i + 1) % map->width == 0)
        {
            printf("\n");
        }
    }
    // recover the map.stringify
    memcpy(map->stringify, agent->originMapStringify, strlen(map->stringify) + 1);
    free(answer);
    return AgentFunOk;
}
void agent_printPermutation(AgentPermutation_t per, size_t perCount)
{
    printf("Permutation:\n\t");
    for (int i = 0; i < perCount; i++)
    {
        printf("%d", per[i]);
    }
    printf("\n");
}

AgentFun_t agent_auto(Agent_t *agent, size_t count)
{
    AgentFun_t result = AgentFunFail;
    AgentFun_t attempts = 1;
    // make all permutation
    AgentPermutation_t permutation = malloc(sizeof(uint8_t) * count);
    // init the permutation
    for (size_t i = 0; i < count; i++)
    {
        permutation[i] = i;
    }
    // check the first permutation
    if (agent_verificationPermutation(agent, permutation, count) == AgentFunOk)
    {
        agent_printAnswer(agent, permutation, count);
        result = AgentFunOk;
        goto _result;
    }
    // The others permutation
    while (1)
    {
        int j = count - 2;
        while (j >= 0 && permutation[j] > permutation[j + 1])
        {
            --j;
        }
        if (j < 0)
        {
            break;
        }
        int k = count - 1;
        while (permutation[j] > permutation[k])
        {
            --k;
        }
        // swap j and k
        uint8_t temp = permutation[j];
        permutation[j] = permutation[k];
        permutation[k] = temp;

        int r = count - 1;
        int s = j + 1;
        while (r > s)
        {
            temp = permutation[r];
            permutation[r] = permutation[s];
            permutation[s] = temp;
            --r;
            ++s;
        }
        // call the agent to check the permutation
        attempts++;
        if (agent_verificationPermutation(agent, permutation, count) == AgentFunOk)
        {
            result = AgentFunOk;
            printf("attempts:%d\n", attempts);
            agent_printPermutation(permutation, count);
            agent_printAnswer(agent, permutation, count);
            goto _result;
        }
    }
_result:
    free(permutation);
    return result;
}
