#ifndef _BYS_BIT_PARSER_H_
#define _BYS_BIT_PARSER_H_
#include <stdbool.h>
#include <stddef.h>
#include "bys.h"

void bp_stringTobit(BitUint_t *uintDst, BlockStringify_t stringify);

/**
 * @brief BitUint_t to BlockStringify_t
 *
 * @param dst
 * @param dstSize
 * @param bit
 */
void bp_bitToString(BlockStringify_t *dst, size_t dstSize, BitUint_t bit);
/**
 * @brief array Block_t to BlockStringify_t
 * Please dstSize >= arrSize+1, and init the dst
 * left Padding zero
 *
 * @param dst target
 * @param dstSize  target size
 * @param arr source
 * @param arrSize source size
 */
void bp_arrayToStringify(BlockStringify_t *dst, size_t dstSize, Block_t *arr, size_t arrSize);

/**
 * @brief check the input(binary)have 1
 *
 * @param bit
 * @return true The input(binary) have 1
 * @return false The input(binary) don't have 1
 */
bool bp_bitwiseHaveTrueBit(BitUint_t bit);
#endif