#include "token.h"

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
TokenType LookupIdent(String ident)
{
    if (StringEquals(ident, StringFromLiteral("fn")))
    {
        return FUNCTION;
    }
    else if (StringEquals(ident, StringFromLiteral("let")))
    {
        return LET;        
    }
    else
    {
        return IDENT;
    }
}

Token NextToken(Lexer* lexer)
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
                TokenType type = LookupIdent(ident);
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
