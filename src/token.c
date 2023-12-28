#include "token.h"

const char* fn_keyword = "fn";
const char* let_keyword = "let";
String keywords[2];
TokenType types[2];

KeywordMap InitKeywords()
{
    keywords[0] = StringFromCString(fn_keyword);
    keywords[1] = StringFromCString(let_keyword);
    types[0] = FUNCTION;
    types[1] = LET;
    KeywordMap keyword_map = {
        .keywords = keywords,
        .token_types = types,
        .len = 2
    };
    return keyword_map;
}

Token NewToken(TokenType type, u8 ch)
{
    Token token = {
        .type = type,
        .literal = StringFromChar(ch)
    };

    return token;
}

Token NewTokenFromLiteral(TokenType type, String lit)
{
    Token token = {
        .type = type,
        .literal = lit
    };

    return token;
}

// TODO: This is the dumbest possible version of lookup. Should be reworked
TokenType LookupIdent(KeywordMap map, String ident)
{
    for (usize i = 0; i < map.len; i++)
    {
        if (StringEquals(ident, map.keywords[i]))
        {
            return map.token_types[i];
        }
    }

    return IDENT;
}

Token NextToken(KeywordMap map, Lexer* lexer)
{
    Token token;

    SkipWhitespace(lexer);

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
        default:
        {
            if (IsLetter(lexer->ch))
            {
                String ident = ReadIdentifier(lexer);
                TokenType type = LookupIdent(map, ident);
                token = NewTokenFromLiteral(type, ident);
                return token;
            }
            else if (IsDigit(lexer->ch))
            {
                String number = ReadNumber(lexer);
                token = NewTokenFromLiteral(INT, number);
                return token;
            }
            else
            {
                token = NewToken(ILLEGAL, lexer->ch);
            }
            break;
        }
    }

    ReadChar(lexer);
    return token;
}
