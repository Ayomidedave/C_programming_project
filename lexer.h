#ifndef LEXER_H
#define LEXER_H

typedef enum
{
    ENCRYPT,
    ARCHIVE,
    RESTORE,
    SYNC,
    ALERT,
    LOG,
    EXPORT,
    IMPORT,
    VALIDATE,
    CREATE,
    UPDATE,
    DELETE,
    SCHEDULE,
    CANCEL,
    GENERATE,
    RETRIEVE,
    SEARCH,
    CHECK,
    AUTHENTICATE,
    IDENTIFIER,
    END_OF_FILE,
    INVALID_TOKEN
} TokenType;

typedef struct
{
    TokenType type;
    char lexeme[100];
} Token;

extern const char *keywords[];
extern const char *commands[];

void initialize_lexer(const char *code);
Token get_next_token();

#endif
