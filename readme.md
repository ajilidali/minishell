Reference a revoir pour comprendre variable env 'globale'

ERREURS :

- Le export, quand execute sans arguments, mange une partie des envp, en les effacant effectivement de la liste envp, j'ai donc desactive de facon temporaire le sort alphabetique. En vrai osef

< ./readme.md cat OK
echo bla > test.txt bla2 OK
ec''ho blabla KO
fct parse_command broken in smaller fcts
~ Moved to parsecmd
Cleaned utils
Fixed SIGSEGV in calculate_output_length(ft_replace) : "ls \n"
FOUND BUG, Invalid Free, cause : <<EOF | ls

- Faire en sorte de modifier la valeur exit quand signal avec variable globale
- Signal pour ctrl + \ ne marche pas bien dutout notament avec cat
- Signal pour ctrl + z fait truc bizarre
- here doc fonctionne mais pas a son prime
- seg fault quand je fais echo $?
ATTENTION CTRL+Z FAIT UN TRUC BIZARD

Arbre AST pour comprendre comment c'est fait :

![alt text](<Screenshot from 2024-06-19 19-27-15.png>)

