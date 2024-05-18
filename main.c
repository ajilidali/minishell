#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

char *rl_shell (char *line_read);

int main(void)
{
    char *line;
    line = (char *)NULL;

    while ((line = rl_shell(line)))
        printf("You entered: %s\n", line);
   /* while((line = readline("con > ")))
    {
        printf("You entered: %s\n", line);
   //     rl_on_new_line();
    }*/
}

char *rl_shell (char *line_read)
{
    if (line_read)
    {
        free (line_read);
        line_read = (char *)NULL;
    }
    line_read = readline ("blyat > ");
    if(strcmp(line_read, "exit") == 0)
    {
        rl_clear_history();
        free(line_read);
        exit(0); 
    }
    if (line_read && *line_read)
        add_history (line_read);
    return (line_read);
}