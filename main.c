#include <stdio.h>
#include "lexer.h"
#include "parser.h"

int main()
{
    const char *code = "encrypt archive sync create delete search";

    initialize_lexer(code);
    parse_program();

    return 0;
}
