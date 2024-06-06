			/*	if (strcmp(mini->line, "testenv") == 0)
			{
					test_envp(give_envp(NULL,0),"susaaafff");
					//update_envp(mini);
			}
			if (strcmp(mini->line, "diffcheck") == 0)
			{
					test_envp(give_envp(NULL,0),"actually up to date");
			}*/ 

Reference a revoir pour comprendre variable env 'globale'

Pour mieux comprendre : la fonction give_envp utilisee une fois pendant l'initialisation de envp va garder dans sa variable statique le pointeur de envp,
une fois appellee avec les arguments NULL et 0 elle va juste rendre le pointeur de envp, ceci est un raccourci pour eviter de se trimballer la structure du shell tout au long de plusieures fonctions avec le  unique but d'utiliser envp.

Le export, quand execute sans arguments, mange une partie des envp, en les effacant effectivement de la liste envp