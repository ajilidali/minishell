#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../includes/libft.h"
#include "../includes/pipex.h"

int executor(char *line, char **envp);
char *rl_shell(char *line_read);
char **lexer(char *line);

int main(int argc, char **argv, char **envp)
{
    if (getpid() != 0)
    { 
        char **lex; 
        (void)argc;
        (void)envp;
        (void)argv;
        char *line = NULL;
        
        while ((line = rl_shell(line)))
        {
            printf("You entered: %s\n", line);
            lex = lexer(line);
            for (int i = 0; lex[i]; i++)
                printf("lex[%d] = %s\n", i, lex[i]);
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

char **lexer(char *line)
{
    int bufsize = 64;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " ");
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " ");
    }
    tokens[position] = NULL;
    return tokens;
}