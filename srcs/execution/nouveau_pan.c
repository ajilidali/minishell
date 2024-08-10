#include "../../includes/minishell.h"

list_commands *create_list_node(ASTNode *node)
{
    list_commands *new_node = (list_commands *)malloc(sizeof(list_commands));
    if (!new_node)
        return NULL;
    new_node->args = node->args;
	new_node->fd_in = node->fd_in;
	new_node->fd_out = node->fd_out;
	new_node->redirections = node->redirections;
	new_node->redirections_count = node->redirections_count;
	new_node->redirections_capacity = node->redirections_capacity;
	new_node->save_in = node->save_in;
	new_node->save_out = node->save_out;
    new_node->next = NULL;
    return new_node;
}

// Fonction pour ajouter un nœud à la liste chaînée
void add_to_list(list_commands **head, ASTNode *node)
{
    list_commands *new_node = create_list_node(node);
	list_commands *temp;

    if (!new_node)
        return;

    if (*head == NULL)
        *head = new_node;
    else
    {
		temp = *head;
        while (temp->next)
            temp = temp->next;
        temp->next = new_node;
    }
}

// Fonction pour copier l'AST dans une liste chaînée
void copy_ast_in_list(ASTNode *node, list_commands **head) {
    if (!node) 
		return;
    if (node->type == AST_COMMAND) { // Supposons que COMMAND_NODE_TYPE représente un nœud de commande
        list_commands *new_node = create_list_node(node);

        // Ajouter le nouveau nœud à la fin de la liste chaînée
        if (*head == NULL) {
            *head = new_node;
        } else {
            list_commands *temp = *head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = new_node;
        }
    }

    // Récursion sur les sous-arbres gauche et droit pour les nœuds PIPE
    copy_ast_in_list(node->left, head);
    copy_ast_in_list(node->right, head);
}
