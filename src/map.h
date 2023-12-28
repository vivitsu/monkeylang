#ifndef MAP_H
#define MAP_H

#include "types.h"
#include "string.h"
#include "token.h"

/*
 * Implementation of a basic hashmap aka associative array.
 * Mostly borrowed from Per Vognsen's Bitwise project:
 * 
 * https://github.com/pervognsen/bitwise/blob/master/ion/common.c
 */

typedef struct Map
{
    u64* keys;
    u64* vals;
    usize len;
    usize cap;
} Map;

void* MapGet(Map* map, const void* key);
void MapPut(Map* map, const void* key, void* val);

#endif