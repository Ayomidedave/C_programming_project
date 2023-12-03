#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

static const char *keywords[] = {
    "encrypt", "archive", "restore", "sync", "alert", "log", "export", "import",
    "validate", "create", "update", "delete", "schedule", "cancel", "generate",
    "retrieve", "search", "check", "authenticate"};

static const int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

static const char *commands[] = {
    "Encrypts sensitive data for security.",
    "Archives old data for record-keeping and reduces system clutter.",
    "Restores data from archives when needed.",
    "Synchronizes data across different systems or databases.",
    "Generates alerts or reminders for specific conditions or events.",
    "Records events or changes for audit trails and monitoring.",
    "Exports data in various formats for external use.",
    "Imports data from external sources into the system.",
    "Validates data inputs for accuracy and compliance.",
    "Used to create new entries, e.g., patient profiles or records.",
    "Updates existing data, like modifying patient information.",
    "Removes data entries, such as deleting old records.",
    "For scheduling appointments or events.",
    "Cancels scheduled appointments or events.",
    "Generates reports, invoices, or other documents.",
    "Fetches and displays data, like patient details or records.",
    "Searches for specific data based on given criteria.",
    "Checks conditions, such as availability of resources.",
    "Handles user authentication and authorization processes."};

static const int num_commands = sizeof(commands) / sizeof(commands[0]);

static const char *code;
static int current_position = 0;

void initialize_lexer(const char *input_code)
{
    code = input_code;
    current_position = 0;
}

Token get_next_token()
{
    Token token;

    // Skip whitespace
    while (code[current_position] == ' ' || code[current_position] == '\t')
    {
        current_position++;
    }

    // Check for end of file
    if (code[current_position] == '\0')
    {
        token.type = END_OF_FILE;
        strcpy(token.lexeme, "");
        return token;
    }

    // Check for identifiers
    int i;
    for (i = 0; i < num_keywords; i++)
    {
        if (strncmp(code + current_position, keywords[i], strlen(keywords[i])) == 0 &&
            !isalnum(code[current_position + strlen(keywords[i])]))
        {
            token.type = i;
            strncpy(token.lexeme, code + current_position, strlen(keywords[i]));
            token.lexeme[strlen(keywords[i])] = '\0';
            current_position += strlen(keywords[i]);
            return token;
        }
    }

    // Invalid token
    token.type = INVALID_TOKEN;
    strncpy(token.lexeme, code + current_position, 1);
    token.lexeme[1] = '\0';
    current_position++;
    return token;
}
