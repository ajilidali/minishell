typedef struct ASTNode {
	ASTNodeType		type;
	char			**args; // For command nodes
	int				fd_in;
	int				fd_out;
	int				save_in;
	int				save_out;
	struct ASTNode	*left; // For pipe nodes
	struct ASTNode	*right; // For pipe nodes
	t_redirection	*redirections; // Array containing redirections
	size_t			redirections_count; // Number of redirections
	size_t			args_capacity;
	size_t			redirections_capacity;
	size_t			args_count;
} ASTNode;

typedef struct list_commands {
	struct list_commands next;
	char **args;
	int	fd_in;
	int fd_out;
	int save_in;
	int save_out;
	t_redirection 	*redirections;
	size_t			redirections_count; // Number of redirections
	size_t			args_capacity;
	size_t			redirections_capacity;
	size_t			args_count;

} list_commands;

list_commands *create_list_node(ASTNode *node)
{
    list_commands *new_node = (list_commands *)malloc(sizeof(list_commands));
    if (!new_node)
        return NULL;
    new_node->args = ft_strdup(node->args);
	new_node->fd_in = node->fd_in;
	new_node->fd_out = node->fd_out;
	new_node->redirections = node->redirections;
	new_node->save_in = node->save_in;
	new_node->save_out = node->save_out;
    new_node->next = NULL;
    return new_node;
}

// Fonction pour ajouter un nœud à la liste chaînée
void add_to_list(list_commands **head, ASTNode *node)
{
    list_commands *new_node = create_list_node(node);

    if (!new_node)
        return;

    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        list_commands *temp = *head;
        while (temp->next)
            temp = temp->next;
        temp->next = new_node;
    }
}

// Fonction pour copier l'AST dans une liste chaînée
void copy_ast_in_list(ASTNode *ast, t_list **list)
{
    if (!ast)
        return;

    // Ajouter le nœud actuel à la liste
    add_to_list(list, ast);

    // Parcourir récursivement les sous-arbres gauche et droit
    copy_ast_in_list(ast->left, list);
    copy_ast_in_list(ast->right, list);
}