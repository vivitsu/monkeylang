#include "types.h"
#include <string.h>
#include <stdlib.h>

typedef struct String
{
    char* data;
    u32 len;
} String;

String NewString(char *data, int len)
{
    char *new = malloc(sizeof(char) * len);
    strncpy(new, data, len);
    String str = {
        .data = new,
        .len = len
    };

    return str;
}
