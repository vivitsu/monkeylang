#include "string.c"

typedef enum TokenType 
{
    ILLEGAL = 1,
    EOF = 2,

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

typedef struct Lexer {
    String input;
    u32 pos;
    u32 read_pos;
    u8 ch;
} Lexer;

void ReadChar(Lexer* lexer) 
{
    if (lexer->read_pos >= lexer->input.len)
    {
        lexer->ch = 0;
    }
    else
    {
        lexer->ch = lexer->input.data[lexer->read_pos];
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

Token NewToken(TokenType type, u8 ch)
{
    char lit[] = { ch, 0 }; 
    Token token = {
        .type = type,
        .literal = NewString(lit, 1)
    };

    return token;
}

Token NextToken(Lexer lexer) 
{
    Token token;

    switch(lexer.ch)
    {
        case '=':
        {
            token = NewToken(ASSIGN, lexer.ch);
        }
    }

    ReadChar(&lexer);
    return token;
}