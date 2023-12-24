#include "lexer.h"

boolean IsLetter(u8 ch)
{
    if (('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ch == '_')
    {
        return true;
    }
    return false;
}

boolean IsDigit(u8 ch)
{
    if (('0' <= ch) && (ch <= '9'))
    {
        return true;
    }
    return false;
}

String ReadIdentifier(Lexer* lexer)
{
    u64 current_pos = lexer->pos;
    while (IsLetter(lexer->ch))
    {
        ReadChar(lexer);
    }

    return Slice(lexer->input, current_pos, lexer->pos);
}

String ReadNumber(Lexer* lexer)
{
    u64 current_pos = lexer->pos;
    while (IsDigit(lexer->ch))
    {
        ReadChar(lexer);
    }

    return Slice(lexer->input, current_pos, lexer->pos);
}

void ReadChar(Lexer* lexer)
{
    if (lexer->read_pos >= Size(lexer->input))
    {
        lexer->ch = 0;
    }
    else
    {
        lexer->ch = CharAt(lexer->input, lexer->read_pos);
    }

    lexer->pos = lexer->read_pos;
    lexer->read_pos += 1;
}

Lexer NewLexer(String input)
{
    Lexer lexer = {
        .input = input,
        .pos = 0,
        .read_pos = 0,
        .ch = 0
    };
    ReadChar(&lexer);
    return lexer;
}

void SkipWhitespace(Lexer* lexer)
{
    while (lexer->ch == ' ' || lexer->ch == '\t' || lexer->ch == '\n' || lexer->ch == '\r')
    {
        ReadChar(lexer);
    }
}