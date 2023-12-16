// interpreter.c

#include "interpreter.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

void interpret(AstNode *ast)
{
    if (ast != NULL)
    {
        switch (ast->type)
        {
        case AST_PROGRAM:
            interpret_program(ast);
            break;
        case AST_COMMAND:
            interpret_command(ast);
            break;
        case AST_EXPRESSION:
            interpret_expression(ast);
            break;
        case AST_IDENTIFIER:
            interpret_identifier(ast);
            break;
        case AST_LITERAL:
            interpret_literal(ast);
            break;
        case AST_ARGUMENT_LIST:
            interpret_argument_list(ast);
            break;
        // Add more cases as needed
        default:
            fprintf(stderr, "Error: Unknown AST node type.\n");
            break;
        }
    }
}

void interpret_program(AstNode *program_node)
{
    if (program_node->children != NULL)
    {
        for (int i = 0; program_node->children[i] != NULL; ++i)
        {
            interpret(program_node->children[i]);
        }
    }
}

void interpret_command(AstNode *command_node)
{
    switch (command_node->command_type)
    {
    case ENCRYPT:
        interpret_encrypt(command_node);
        break;
    case ARCHIVE:
        interpret_archive(command_node);
        break;
    case SYNC:
        interpret_sync(command_node);
        break;
    case CREATE:
        interpret_create(command_node);
        break;
    case DELETE:
        interpret_delete(command_node);
        break;
    case SEARCH:
        interpret_search(command_node);
        break;
    case AUTHENTICATE:
        interpret_auhenticate(command_node);
    default:
        fprintf(stderr, "Error: Unknown command type.\n");
        break;
    }
}

void interpret_expression(AstNode *expression_node)
{
    printf("Interpreting expression\n");
}

void interpret_identifier(AstNode *identifier_node)
{
    printf("Interpreting identifier: %s\n", get_identifier_value(identifier_node));
}

void interpret_literal(AstNode *literal_node)
{
    printf("Interpreting literal: %s\n", get_literal_value(literal_node));
}

void interpret_argument_list(AstNode *argument_list_node)
{
    if (argument_list_node->children != NULL)
    {
        for (int i = 0; argument_list_node->children[i] != NULL; ++i)
        {
            interpret(argument_list_node->children[i]);
        }
    }
}

void interpret_encrypt(AstNode *command_node)
{
    printf("Executing 'encrypt' command.\n");
}

void interpret_archive(AstNode *command_node)
{
    printf("Executing 'archive' command.\n");
}

void interpret_sync(AstNode *command_node)
{
    printf("Executing 'sync' command.\n");
}

void interpret_create(AstNode *command_node)
{
    printf("Executing 'create' command.\n");
}

void interpret_delete(AstNode *command_node)
{
    printf("Executing 'delete' command.\n");
}

void interpret_search(AstNode *command_node)
{
    printf("Executing 'search' command.\n");
}
