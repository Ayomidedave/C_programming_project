#include <stdio.h>
#include "lexer.h"

int main()
{
    const char *code = "encrypt archive sync create delete search";

    initialize_lexer(code);

    Token token;
    do
    {
        token = get_next_token();
        switch (token.type)
        {
        case ENCRYPT:
        case ARCHIVE:
        case SYNC:
        case CREATE:
        case DELETE:
        case SEARCH:
            printf("Command: %s\nDescription: %s\n", keywords[token.type], commands[token.type]);
            break;
        case END_OF_FILE:
            printf("End of File\n");
            break;
        case INVALID_TOKEN:
            printf("Invalid Token: %s\n", token.lexeme);
            break;
        default:
            printf("Unknown Token\n");
        }
    } while (token.type != END_OF_FILE);

    return 0;
}
