#ifndef STRING_H
#define STRING_H

#include "types.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct String
{
    u8* data;
    u64 len;
} String;

u64 CalculateCStringSize(char* str);
String CreateString(u8* data, u64 len);
boolean StringEquals(String s1, String s2);
String StringFromChar(u8 ch);
void PrintString(String string);

#define StringFromLiteral(lit) CreateString((u8 *)lit, sizeof(lit) - 1)
#define StringFromCString(cstring) CreateString((u8 *)cstring, CalculateCStringSize(cstring))

#endif