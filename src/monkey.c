#include "lexer.c"
#include <assert.h>

int main(int argc, char** argv)
{
    char* data = "=+(){};";
    // char *data = "=";
    String input = StringFromCString(data);
    Lexer* lexer = NewLexer(input);
    u64 size = Size(input);
    Token tests[] = {
        {ASSIGN, StringFromLiteral("=")},
        {PLUS, StringFromLiteral("+")},
        {LPAREN, StringFromLiteral("(")},
        {RPAREN, StringFromLiteral(")")},
        {LBRACE, StringFromLiteral("{")},
        {RBRACE, StringFromLiteral("}")},
        {SEMICOLON, StringFromLiteral(";")}
    };

    for (u64 index = 0; index < size; index++)
    {
        Token actual = NextToken(lexer);
        Token expected = tests[index];
        assert((actual.type == expected.type));
        assert(StringEquals(actual.literal, expected.literal));
    }

    return 0;
}
