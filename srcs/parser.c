/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:19:54 by moajili           #+#    #+#             */
/*   Updated: 2024/05/22 17:35:51 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

Parser parser_init(const char *input) {
    Parser parser;
    parser.lexer = lexer_init(input);
    parser.current_token = lexer_next_token(&parser.lexer);
    return parser;
}

// Prochain Token
void parser_advance(Parser *parser)
{
    if (parser->current_token.value)
        free(parser->current_token.value);
    parser->current_token = lexer_next_token(&parser->lexer);
}

// Parse la commande
ASTNode *parse_command(Parser *parser)
{
    ASTNode *node;
    size_t capacity;
    size_t count;

    node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = AST_COMMAND;
    node->left = node->right = NULL;
    capacity = 10;
    count = 0;
    node->args = (char **)malloc(capacity * sizeof(char *));

    while (parser->current_token.type == TOKEN_WORD)
    {
        if (count >= capacity)
        {
            capacity *= 2;
            free(node->args);
            node->args = (char **)malloc(capacity * sizeof(char *));
        }
        node->args[count++] = strdup(parser->current_token.value);
        parser_advance(parser);
    }
    node->args[count] = NULL;
    return node;
}

// Parsing du pipe
ASTNode *parse_pipeline(Parser *parser)
{
    ASTNode *left;
    ASTNode *node;

    left = parse_command(parser);
    while (parser->current_token.type == TOKEN_OPERATOR && strcmp(parser->current_token.value, "|") == 0)
    {
        node = (ASTNode *)malloc(sizeof(ASTNode));
        node->type = AST_PIPELINE;
        node->left = left;
        parser_advance(parser);
        node->right = parse_command(parser);
        left = node;
    }
    return left;
}

// Free AST
/*void free_ast(ASTNode *node)
{
    if (!node)
        return;
    if (node->type == AST_COMMAND)
    {
        for (char **arg = node->args; *arg; arg++) 
        {
            free(*arg);
        }
        free(node->args);
    } 
    else if (node->type == AST_PIPELINE)
    {
        free_ast(node->left);
        free_ast(node->right);
    }
    free(node);
}*/
void free_ast(ASTNode *node)
{
    char **arg;

    if (!node)
        return;
    if (node->type == AST_COMMAND)
    {
        arg = node->args;
        while (*arg)
        {
            free(*arg);
            arg++;
        }
        free(node->args);
    } else if (node->type == AST_PIPELINE) {
        free_ast(node->left);
        free_ast(node->right);
    }
    free(node);
}



// Execution du AST
void execute_ast(ASTNode *node)
{
    int pipefd[2];

    if (!node)
        return;
    if (node->type == AST_COMMAND)
    {
        if (fork() == 0)
        {
            execvp(node->args[0], node->args);
            perror("execve");
            exit(1);
        }
        else
            wait(NULL);
    } 
    else if (node->type == AST_PIPELINE) 
    {
        pipe(pipefd);
        ft_fork_left(node->left,pipefd);
        ft_fork_right(node->right,pipefd);
        close(pipefd[0]);
        close(pipefd[1]);
        wait(NULL);
        wait(NULL);
    }
}

void ft_fork_right(ASTNode *node, int pipefd[2])
{
    if (fork() == 0) 
    {
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        execute_ast(node);
        exit(0);
    }
}
void ft_fork_left(ASTNode *node, int pipefd[2])
{
    if (fork() == 0)
    {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        execute_ast(node);
        exit(0);
    }
}
