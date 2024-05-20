/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:50:54 by moajili           #+#    #+#             */
/*   Updated: 2024/05/20 17:58:13 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

Token *lex(const char *input);


int main(int argc, char **argv, char **envp)
{
    if (getpid() != 0)
    { 
        (void)argc;
        (void)argv;
        char *line = NULL;
        Token *tokens;
        
        while ((line = rl_shell(line)))
        {
            printf("You entered: %s\n", line);
            
            tokens = lex(line);

            for (int i = 0; tokens[i].type; i++)
            {
                printf("Token Type: %d, Value: %s\n", (int)tokens[i].type != -1, tokens[i].value);
            }

            executor(line, envp);
        }
    }
    return 0;
}

int executor(char *line, char **envp)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
        return (perror("fork"),EXIT_FAILURE);
    if (pid == 0)
    {
        fprintf(stderr, "\033[36;1mProcess child: %d\033[m\n", getpid());
        if (execute(line, envp) == -1)
        {
            perror("execute");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        else
            printf("Child process did not terminate normally\n");
    }
    return EXIT_SUCCESS;
}

char *rl_shell(char *line_read)
{
    if (line_read)
    {
        free(line_read);
        line_read = NULL;
    }
    line_read = readline("DEDSEC > ");
    if (line_read == NULL)
    {
        rl_clear_history();
        exit(0);
    }
    if (strcmp(line_read, "exit") == 0)
    {
        rl_clear_history();
        free(line_read);
        exit(0); 
    }
    if (line_read && *line_read)
        add_history(line_read);
    return line_read;
}



Token *lex(const char *input)
{
    Token *tokens = (Token *)malloc(sizeof(Token) * MAX_TOKEN_COUNT);
    if (tokens == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    int token_count = 0;
    char *token_start = strtok((char *)input, " "); 

    while (token_start != NULL && token_count < MAX_TOKEN_COUNT - 1)
    {
        TokenType type;

        if (isdigit(*token_start))
            type = TOKEN_NBR;
        else if (strcmp(token_start, "|") == 0)
            type = TOKEN_PIPE;
        else 
            type = TOKEN_CMD;
        
        strncpy(tokens[token_count].value, token_start, MAX_TOKEN_LENGTH - 1);
        tokens[token_count].value[MAX_TOKEN_LENGTH - 1] = '\0';
        tokens[token_count].type = type;

        token_start = strtok(NULL, " ");
        token_count++;
    }

    tokens[token_count].type = TOKEN_TERMINATOR;
    tokens[token_count].value[0] = '\0';

    return tokens;
}


