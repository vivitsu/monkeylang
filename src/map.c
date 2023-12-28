#include "map.h"
#include "common.h"
#include <assert.h>
#include <stdlib.h>

/*
 * djb2: http://www.cse.yorku.ca/~oz/hash.html
 */
// internal u32 HashString(const String s)
// {
//     u32 hash = 5381;
//     u8 c;

//     for (usize index = 0; index < s.len; index++)
//     {
//         c = s.data[index];
//         /* hash * 33 + c */
//         hash = ((hash << 5) + hash) + c;
//     }

//     return hash;
// }

internal u64 HashU64(u64 key)
{
    key *= 0xff51afd7ed558ccd;
    key ^= key >> 32;
    return key;
}

internal u64 MapGetU64FromU64(Map* map, u64 key)
{
    if (map->len == 0)
    {
        return 0;
    }

    assert(IS_POW2(map->cap));
    usize index = (usize) HashU64(key);
    assert(map->len < map->cap);

    for(;;)
    {
        index &= map->cap - 1;
        if (map->keys[index] == key)
        {
            return map->vals[index];
        }
        else if (!map->keys[index])
        {
            return 0;
        }
        index++;
    }
}

void* MapGet(Map* map, const void* key)
{
    return (void *)(uintptr_t)MapGetU64FromU64(map, (u64)(uintptr_t)key);
}

internal void MapPutU64FromU64(Map* map, u64 key, u64 val);

internal void MapGrow(Map* map, usize new_cap)
{
    new_cap = CLAMP_MIN(new_cap, 16);
    Map new_map = {
        .keys = calloc(new_cap, sizeof(u64)),
        .vals = malloc(new_cap * sizeof(u64)),
        .cap = new_cap
    };

    for (usize i = 0; i < map->cap; i++)
    {
        if (map->keys[i])
        {
            MapPutU64FromU64(&new_map, map->keys[i], map->vals[i]);
        }
    }

    free((void *)map->keys);
    free(map->vals);
    *map = new_map;
}

internal void MapPutU64FromU64(Map* map, u64 key, u64 val)
{
    assert(key);
    if (!val)
    {
        return;
    }
    
    if (2 * map->len >= map->cap)
    {
        MapGrow(map, 2 * map->cap);
    }

    assert(2 * map->len < map->cap);
    assert(IS_POW2(map->cap));

    usize index = (usize) HashU64(key);

    for (;;)
    {
        // Make sure index maps in the range of 0..map->cap
        index &= map->cap - 1;
        if (!map->keys[index])
        {
            map->len++;
            map->keys[index] = key;
            map->vals[index] = val;
            return;
        }
        else if (map->keys[index] == key)
        {
            map->vals[index] = val;
            return;
        }
        index++;
    }

}

void MapPut(Map* map, const void* key, void* val)
{
    MapPutU64FromU64(map, (u64)(uintptr_t)key, (u64)(uintptr_t)val);
}