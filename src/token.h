#ifndef TOKEN_H
#define TOKEN_H

#include "lexer.h"

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

typedef struct KeywordMap
{
    String* keywords;
    TokenType* token_types;
    usize len;
} KeywordMap;

KeywordMap* InitKeywords();
void FreeKeywordMap(KeywordMap* map);
Token NewToken(TokenType type, u8 ch);
Token NewTokenFromLiteral(TokenType type, String lit);
Token NextToken(KeywordMap* map, Lexer* lexer);
TokenType LookupIdent(KeywordMap* map, String ident);

#endif