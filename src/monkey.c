#include "lexer.c"
#include <assert.h>

int main(int argc, char** argv)
{
    // char* data = "=+(){};";
    char *data = "=";
    String input = StringFromCString(data);
    Lexer lexer = NewLexer(input);
    Token token = NextToken(lexer);

    assert(token.type == ASSIGN);
    assert(StringEquals(input, token.literal) == true);
    return 0;
}
