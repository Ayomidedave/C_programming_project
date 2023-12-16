// parser.c
#include "parser.h"
#include "lexer.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

static Token current_token;

// Function prototypes
static void advance();
static AstNode *parse_program();
static AstNode *parse_statement();
static AstNode *parse_command_statement();
static AstNode *parse_expression_statement();
static AstNode *parse_argument_list();
static AstNode *parse_argument();

void parse(const char *code)
{
    initialize_lexer(code);
    advance(); // Load the first token
    AstNode *ast = parse_program();
    // Now you have the AST, you can traverse or execute it as needed.
    // Implement your logic here.

    // Free the allocated memory for the AST
    // Assuming you have a function to free the AST nodes
    free_ast(ast);
}

void advance()
{
    current_token = get_next_token();
}

AstNode *create_ast_node(AstNodeType type)
{
    AstNode *node = (AstNode *)malloc(sizeof(AstNode));
    node->type = type;
    node->children = NULL;
    return node;
}

AstNode *parse_program()
{
    AstNode *program_node = create_ast_node(AST_PROGRAM);
    program_node->children = NULL;

    while (current_token.type != END_OF_FILE)
    {
        AstNode *statement_node = parse_statement();
        // Add statement_node to the program_node's children
        add_child(program_node, statement_node);
    }

    return program_node;
}

AstNode *parse_statement()
{
    if (current_token.type == ENCRYPT || current_token.type == ARCHIVE || current_token.type == SYNC ||
        current_token.type == CREATE || current_token.type == DELETE || current_token.type == SEARCH)
    {
        return parse_command_statement();
    }
    else
    {
        // For simplicity, assuming anything else is an expression statement
        return parse_expression_statement();
    }
}

AstNode *parse_command_statement()
{
    AstNode *command_node = create_ast_node(AST_COMMAND);
    command_node->command_type = current_token.type;

    advance(); // Consume the command token

    if (current_token.type == IDENTIFIER)
    {
        // Add logic to handle the identifier (e.g., store it in the AST)
        AstNode *identifier_node = create_ast_node(AST_IDENTIFIER);
        set_identifier_value(identifier_node, current_token.lexeme);
        add_child(command_node, identifier_node);
        advance();
    }
    else
    {
        // Handle error: expected an identifier
        fprintf(stderr, "Error: Expected an identifier.\n");
        free_ast(command_node); // Free partially constructed AST
        return NULL;
    }

    // Add more logic as needed

    return command_node;
}

AstNode *parse_expression_statement()
{
    AstNode *expression_node = create_ast_node(AST_EXPRESSION);

    if (current_token.type == IDENTIFIER)
    {
        // Add logic to handle the identifier (e.g., store it in the AST)
        AstNode *identifier_node = create_ast_node(AST_IDENTIFIER);
        set_identifier_value(identifier_node, current_token.lexeme);
        add_child(expression_node, identifier_node);
        advance();
    }
    else
    {
        // Handle error: expected an identifier
        fprintf(stderr, "Error: Expected an identifier.\n");
        free_ast(expression_node); // Free partially constructed AST
        return NULL;
    }

    if (current_token.type == '(')
    {
        advance(); // Consume '('

        // Parse the argument list
        AstNode *argument_list_node = parse_argument_list();

        if (current_token.type == ')')
        {
            advance(); // Consume ')'
            add_child(expression_node, argument_list_node);
        }
        else
        {
            // Handle error: expected ')'
            fprintf(stderr, "Error: Expected ')'.\n");
            free_ast(expression_node); // Free partially constructed AST
            return NULL;
        }
    }
    else
    {
        // Handle error: expected '('
        fprintf(stderr, "Error: Expected '('.\n");
        free_ast(expression_node); // Free partially constructed AST
        return NULL;
    }

    return expression_node;
}

AstNode *parse_argument_list()
{
    AstNode *argument_list_node = create_ast_node(AST_ARGUMENT_LIST);
    argument_list_node->children = NULL;

    // Implement logic to parse the argument list and return an AST node for it
    while (current_token.type != ')' && current_token.type != END_OF_FILE)
    {
        AstNode *argument_node = parse_argument();
        add_child(argument_list_node, argument_node);

        if (current_token.type == ',')
        {
            advance(); // Consume ','
        }
        else if (current_token.type != ')' && current_token.type != END_OF_FILE)
        {
            // Handle error: expected ',' or ')'
            fprintf(stderr, "Error: Expected ',' or ')'.\n");
            free_ast(argument_list_node); // Free partially constructed AST
            return NULL;
        }
    }

    return argument_list_node;
}

AstNode *parse_argument()
{
    // Implement logic to parse an argument and return an AST node for it
    AstNode *argument_node = create_ast_node(AST_ARGUMENT);
    argument_node->children = NULL;

    if (current_token.type == IDENTIFIER || current_token.type == STRING_LITERAL || current_token.type == NUMBER_LITERAL)
    {
        AstNode *literal_node = create_ast_node(AST_LITERAL);
        set_literal_value(literal_node, current_token.lexeme);
        add_child(argument_node, literal_node);
        advance();
    }
    else
    {
        // Handle error: expected identifier, string literal, or number literal
        fprintf(stderr, "Error: Expected identifier, string literal, or number literal.\n");
        free_ast(argument_node); // Free partially constructed AST
        return NULL;
    }

    return argument_node;
}
