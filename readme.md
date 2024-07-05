```c
			if (strcmp(mini->line, "testenv") == 0)
			{
					test_envp(give_envp(NULL,0),"susaaafff");
					//update_envp(mini);
			}
			if (strcmp(mini->line, "diffcheck") == 0)
			{
					test_envp(give_envp(NULL,0),"actually up to date");
			}*

//More precisely :
give_envp(envp,COPY);	//Pour que la fonction fasse une copie du envp que t'as fourni et retourne son pointeur, cette fct est utilisee lors de l'initialisation de mini->envp.
give_envp(NULL,0);	//Pour avoir le pointeur de envp sans devoir rien passer.
```
Reference a revoir pour comprendre variable env 'globale'

Pour mieux comprendre : la fonction give_envp utilisee une fois pendant l'initialisation de envp va garder dans sa variable statique le pointeur de envp,
une fois appellee avec les arguments NULL et 0 elle va juste rendre le pointeur de envp, ceci est un raccourci pour eviter de se trimballer la structure du shell tout au long de plusieures fonctions avec le  unique but d'utiliser envp.

Le export, quand execute sans arguments, mange une partie des envp, en les effacant effectivement de la liste envp, j'ai donc desactive de facon temporaire ke sort alphabetique.

< ./readme.md cat OK
echo bla > test.txt bla2 OK
ec''ho blabla KO
fct parse_command broken in smaller fcts
~ Moved to parsecmd
Cleaned utils
Fixed SIGSEGV in calculate_output_length(ft_replace) : "ls \n"

J'ai pas fait les liens symboliques avec cd
Faire en sorte de modifier la valeur exit quand signal avec variable globale
Signal pour ctrl + \ ne marche pas bien dutout notament avec cat
faire here_doc

ATTENTION CTRL+Z FAIT UN TRUC BIZARD
Probleme quand on fait deux commandes avec pipe qui provoquent une erreur les messages d'erreur s'affiche en meme temps
Exemple avec cette commande : srcs/builtins/export.c | srcs/builtins/echo.c

Probleme ligne 67 dans parsecmd lorsque l'on fait par exemple : "ls >" on a le message d'erreur mais le programme continue donc pas bon
avant il y avait un exit(1) mais c'est pas bon.

![alt text](<Screenshot from 2024-06-19 19-27-15.png>)