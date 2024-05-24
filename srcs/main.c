/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:50:54 by moajili           #+#    #+#             */
/*   Updated: 2024/05/24 16:48:54 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

MS g_ms;

int main(int argc, char **argv, char **envp)
{
    if (getpid() != 0)
    {
        (void)argc;
        (void)argv;
        ft_init_ms(envp);

        while ((g_ms.line = rl_shell(g_ms.line)))
        {
           // printf("You entered: %s\n", g_ms.line);

            //Begin lexer
            g_ms.lexer = lexer_init(g_ms.line);
           // g_ms.token = lexer_next_token(&g_ms.lexer);
            g_ms.parser = parser_init(g_ms.line);
            g_ms.ast = parse_pipeline(&g_ms.parser);
            
            if (g_ms.ast)
            {
                execute_ast(g_ms.ast);
                free_ast(g_ms.ast);
            }
            
            
           /* while (g_ms.token.type != TOKEN_EOF) {
                printf("Token: Type = %d, Value = '%s'\n", g_ms.token.type, g_ms.token.value);
                if (g_ms.token.value != NULL)
                    free(g_ms.token.value);
                g_ms.token = lexer_next_token(&g_ms.lexer);
            }*/
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


/*int executor(char *line, char **envp)
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
}*/

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
    if (ft_strcmp(line_read, "exit") == 0)
    {
        rl_clear_history();
        free(line_read);
        exit(0);
    }
    if (line_read && *line_read)
        add_history(line_read);
    return line_read;
}
