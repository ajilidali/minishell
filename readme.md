Reference a revoir pour comprendre variable env 'globale'

Le export, quand execute sans arguments, mange une partie des envp, en les effacant effectivement de la liste envp, j'ai donc desactive de facon temporaire le sort alphabetique.

< ./readme.md cat OK
echo bla > test.txt bla2 OK
ec''ho blabla KO
fct parse_command broken in smaller fcts
~ Moved to parsecmd
Cleaned utils
Fixed SIGSEGV in calculate_output_length(ft_replace) : "ls \n"

- J'ai pas fait les liens symboliques avec cd
- Faire en sorte de modifier la valeur exit quand signal avec variable globale
- Signal pour ctrl + \ ne marche pas bien dutout notament avec cat
- faire here_doc
- s'occuper des exits code pour l'execution

ATTENTION CTRL+Z FAIT UN TRUC BIZARD

Probleme quand on fait deux commandes avec pipe qui provoquent une erreur les messages d'erreur s'affiche en meme temps
Exemple avec cette commande : srcs/builtins/export.c | srcs/builtins/echo.c

Probleme ligne 67 dans parsecmd lorsque l'on fait par exemple : "ls >" on a le message d'erreur mais le programme continue donc pas bon
avant il y avait un exit(1) mais c'est pas bon.

Arbre AST pour comprendre comment c'est fait :

![alt text](<Screenshot from 2024-06-19 19-27-15.png>)