#include "lexer.c"
#include <string.h>
#include <assert.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    // char* data = "=+(){};";
    char* data = "=";
    u32 len = strlen(data);
    String input = NewString(data, len);
    Lexer lexer = NewLexer(input);
    Token token = NextToken(lexer);
    
    assert(token.type == ASSIGN);
    assert(strncmp(token.literal.data, data, 1) == 0);
    return 0;
}