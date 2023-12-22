#include "types.h"
#include "string.h"

u64 CalculateCStringSize(char* str)
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

    for (u64 index = 0; index < s1.len; index++)
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