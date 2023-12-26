#include "types.h"
#include "string.h"
#include <assert.h>

u64 CalculateCStringSize(const char* str)
{
    u64 size = 0;
    for (;str[size];size++);
    return size;
}

String CreateString(u8* data, u64 len)
{
    String str = {
        .data = data,
        .len = len
    };

    return str;
}

boolean StringEquals(String s1, String s2)
{
    if (s1.len != s2.len)
    {
        return false;
    }

    for (usize index = 0; index < s1.len; index++)
    {
        if (s1.data[index] != s2.data[index])
        {
            return false;
        }
    }

    return true;
}

void PrintString(String string)
{
    printf("%.*s\n", (int) string.len, string.data);
}

String StringFromChar(u8 ch)
{
    u8 *buffer = malloc(sizeof(u8));
    buffer[0] = ch;
    String str = {
        .data = buffer,
        .len = 1
    };

    return str;
}

String StringSlice(String s, u64 start, u64 end)
{
    u64 size = end - start;
    assert((size <= s.len));
    u8 *buffer = malloc(sizeof(u8) * size);
    for (usize index = 0; index < size; index++)
    {
        buffer[index] = s.data[start++];
    }

    String str = {
        .data = buffer,
        .len = size
    };

    return str;
}

u8 StringCharAt(String str, u64 index)
{
    if (index >= str.len)
    {
        return 0;
    }
    else
    {
        return str.data[index];
    }
}

u64 StringLength(String str)
{
    return str.len;
}