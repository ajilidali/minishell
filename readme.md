Reference a revoir pour comprendre variable env 'globale'

ERREURS :

- Le export, quand execute sans arguments, mange une partie des envp, en les effacant effectivement de la liste envp, j'ai donc desactive de facon temporaire le sort alphabetique. En vrai osef
- Quand je fais ca : export "OLDPWD=$PWD". La variable OLDPWD est egale a $PWD alors qu'elle devrait etre egale au contenue de $PWD

< ./readme.md cat OK
echo bla > test.txt bla2 OK
ec''ho blabla KO
fct parse_command broken in smaller fcts
~ Moved to parsecmd
Cleaned utils
Fixed SIGSEGV in calculate_output_length(ft_replace) : "ls \n"

- Faire en sorte de modifier la valeur exit quand signal avec variable globale
- Signal pour ctrl + \ ne marche pas bien dutout notament avec cat
- faire here_doc
- s'occuper des exits code pour l'execution

ATTENTION CTRL+Z FAIT UN TRUC BIZARD

Arbre AST pour comprendre comment c'est fait :

![alt text](<Screenshot from 2024-06-19 19-27-15.png>)

