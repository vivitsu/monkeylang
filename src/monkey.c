#include "lexer.h"
#include "token.h"
#include <assert.h>

int main()
{
    char* data = "let five = 5;\nlet ten = 10;";
    String input = StringFromCString(data);
    Lexer lexer = NewLexer(input);
    // size = 9
    Token tests[] = {
        {LET, StringFromLiteral("let")},
        {IDENT, StringFromLiteral("five")},
        {ASSIGN, StringFromLiteral("=")},
        {INT, StringFromLiteral("5")},
        {SEMICOLON, StringFromLiteral(";")},
        {LET, StringFromLiteral("let")},
        {IDENT, StringFromLiteral("ten")},
        {ASSIGN, StringFromLiteral("=")},
        {INT, StringFromLiteral("10")},
        {SEMICOLON, StringFromLiteral(";")}
    };

    for (u64 index = 0; index < 9; index++)
    {
        Token actual = NextToken(&lexer);
        Token expected = tests[index];
        assert((actual.type == expected.type));
        assert(StringEquals(actual.literal, expected.literal));
    }

    return 0;
}
