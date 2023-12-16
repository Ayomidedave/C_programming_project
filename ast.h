// ast.h

#ifndef AST_H
#define AST_H

typedef enum
{
    AST_PROGRAM,
    AST_COMMAND,
    AST_EXPRESSION,
    AST_IDENTIFIER,
    AST_ARGUMENT_LIST,
    AST_ARGUMENT,
    AST_LITERAL,
} AstNodeType;

typedef struct AstNode
{
    AstNodeType type;
    int command_type; // Only for AST_COMMAND nodes
    // Add other fields as needed
    struct AstNode **children; // Array of child nodes
} AstNode;

AstNode *create_ast_node(AstNodeType type);

#endif
