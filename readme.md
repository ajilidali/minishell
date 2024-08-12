ERREURS :

fct parse_command broken in smaller fcts
~ Moved to parsecmd
Cleaned utils
Fixed SIGSEGV in calculate_output_length(ft_replace) : "ls \n"
FOUND BUG, Invalid Free, cause : <<EOF | ls

- Signal pour ctrl + z fait truc bizarre
- quand ls|ls : ls|ls: No such file or directory alors que ca doit renvoyer le resultat d'un ls
ATTENTION CTRL+Z FAIT UN TRUC BIZARD

Arbre AST pour comprendre comment c'est fait :

![alt text](<Screenshot from 2024-06-19 19-27-15.png>)

