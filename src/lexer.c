#include "string.h"

typedef enum TokenType
{
    ILLEGAL = 1,
    END_OF_FILE = 2,

    // Identifiers + literals
    IDENT = 3, // add, foobar, x, y, ...
    INT = 4,   // 1343456

    // Operators
    ASSIGN = 5,
    PLUS = 6,

    // Delimiters
    COMMA = 7,
    SEMICOLON = 8,
    LPAREN = 9,
    RPAREN = 10,
    LBRACE = 11,
    RBRACE = 12,

    // Keywords
    FUNCTION = 13,
    LET = 14
} TokenType;

typedef struct Token
{
    TokenType type;
    String literal;
} Token;

typedef struct Lexer
{
    String input;
    u64 pos;
    u64 read_pos;
    u8 ch;
} Lexer;

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

Lexer* NewLexer(String input)
{
    Lexer* lexer = malloc(sizeof(Lexer));
    lexer->input = input;
    lexer->pos = 0;
    lexer->read_pos = 0;
    lexer->ch = 0;
    ReadChar(lexer);
    return lexer;
}

Token NewToken(TokenType type, u8 ch)
{
    Token token = {
        .type = type,
        .literal = StringFromChar(ch)
    };

    return token;
}

Token NextToken(Lexer* lexer)
{
    Token token;

    switch (lexer->ch)
    {
        case '=':
        {
            token = NewToken(ASSIGN, lexer->ch);
            break;
        };
        case '+':
        {
            token = NewToken(PLUS, lexer->ch);
            break;
        };
        case '(':
        {
            token = NewToken(LPAREN, lexer->ch);
            break;
        };
        case ')':
        {
            token = NewToken(RPAREN, lexer->ch);
            break;
        };
        case '{':
        {
            token = NewToken(LBRACE, lexer->ch);
            break;
        };
        case '}':
        {
            token = NewToken(RBRACE, lexer->ch);
            break;
        };
        case ';':
        {
            token = NewToken(SEMICOLON, lexer->ch);
            break;
        };
    }

    ReadChar(lexer);
    return token;
}
