#include "types.h"

typedef struct String
{
    char* data;
    u32 len;
} String;

String NewString(char* data, int len) 
{
    String str = {
        .data = data,
        .len = len
    };

    return str;
}