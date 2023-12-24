#ifndef LEXER_H
#define LEXER_H

#include "types.h"
#include "string.h"

typedef struct Lexer
{
    String input;
    u64 pos;
    u64 read_pos;
    u8 ch;
} Lexer;

void ReadChar(Lexer* lexer);
Lexer NewLexer(String input);
boolean IsLetter(u8 ch);
boolean IsDigit(u8 ch);
String ReadIdentifier(Lexer* lexer);
String ReadNumber(Lexer* lexer);
void SkipWhitespace(Lexer* lexer);

#endif