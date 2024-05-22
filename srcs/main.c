/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:50:54 by moajili           #+#    #+#             */
/*   Updated: 2024/05/22 17:18:00 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
    if (getpid() != 0)
    { 
        (void)argc;
        (void)argv;
        (void)envp;
        char *line = NULL;
        Lexer lexer;
        Token token;
        
        
        while ((line = rl_shell(line)))
        {
            printf("You entered: %s\n", line);
            lexer = lexer_init(line);



            token = lexer_next_token(&lexer);
            while (token.type != TOKEN_EOF) {
                printf("Token: Type = %d, Value = '%s'\n", token.type, token.value);

                if (token.value != NULL) {
                    free(token.value);
                }
                
                token = lexer_next_token(&lexer);
            }
            //if (strcmp(line, "") != 0)
             //   executor(line, envp);
        }
    }
    return 0;
}

void    print_envp(char **envp)
{
    int i = 0;
    while (envp[i])
    {
        printf("envp[%d]: %s\n", i, envp[i]);
        i++;
    }
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
