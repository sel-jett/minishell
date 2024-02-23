/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:17:58 by amel-has          #+#    #+#             */
/*   Updated: 2024/02/24 00:32:09 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int    add_list_redir(t_node *node)
{
	t_node          *tmp;
	t_node_redir    *redir_node;

	(1 == 1) && (tmp = node, redir_node = NULL);
	node->list_redir = c_list_redir();
	if (!node->list_redir)
		return (0);
	tmp = tmp->next;
	if (tmp && tmp->mode == TOKEN_SPACE)
		tmp = tmp->next;
	while (tmp && (tmp->mode == TOKEN_EXPR || tmp->mode 
	== TOKEN_PARENTHESE || tmp->mode == TOKEN_Double_Q || tmp->mode 
	== TOKEN_Single_Q || tmp->mode == TOKEN_SPACE))
	{
		redir_node =  c_node_redir(tmp->value);
		if (!redir_node)
			return (0);
		add_back_redir(node->list_redir, redir_node);
		tmp = tmp->next;
	}
	return (1);
}
void    print_tree(t_node_arbre    *tree, int c)
{
    int i = 0;
    if (!tree)
        return;
    print_tree(tree->right, c + 5);
    while (i < c)
    {
        printf(" ");
        i++;
    }
    if (tree->mode == 5)
        printf("%c ->\n", '|');
    else if (tree->mode == 7)
        printf("%s ->\n", "||");
    else if (tree->mode == 6)
        printf("%s ->\n", "&&");
    else if (tree->mode == 100)
        printf("%c ->\n", 'C');
    else if (tree->mode == 0)
        printf("%s ->\n", tree->value);
    else if (tree->mode == TOKEN_REDIR_IN)
        printf("%c ->\n", '<');
    else
        printf("%d ->\n", tree->mode);
    // if (tree->mode == 0)
    // {
    //     t_list *tmp ;
    //     tmp = tree->value->redir_in;
    //     while (tmp)
    //     {
    //         printf("redir_in: %s\n", tmp->token);
    //         tmp = tmp->next;
    //     }
    // }
    print_tree(tree->left, c + 5);
}

t_arbre *parse_cmd(t_node **tmp)
{
	t_node	*node;

	if ((*tmp)->mode == TOKEN_PARENTHESE)
		//
	;
	if ((*tmp)->mode == TOKEN_EXPR)
	{
		node = *tmp;
	}
}






// void	search_redir_left(t_node *tmp, t_node_arbre **node,int *n)
// {
// 	if (!tmp)
// 		return ;
// 	if ((tmp->mode == TOKEN_REDIR_APPEND ||  tmp->mode == TOKEN_HEREDOC || tmp->mode == TOKEN_REDIR_APPEND ||tmp->mode == TOKEN_REDIR_IN) && !(tmp->is_visited))
// 	{
// 		printf("ha ana \n");
// 		(*n)++;
// 		tmp->is_visited = 1;
// 		*node = c_node_arbre(tmp);
// 		(*node)->left = c_node_arbre(tmp->prev);
// 		(*node)->right = c_node_arbre(tmp->next);
// 		search_redir_left(tmp->prev, &(*node)->left,n);
// 	}
// 	else
// 		search_redir_left(tmp->prev, node,n);
// }

// void	search_redir_right(t_node *tmp, t_node_arbre **node,int *n)
// {
// 	if (!tmp)
// 		return ;
// 	if ((tmp->mode == TOKEN_REDIR_APPEND ||  tmp->mode == TOKEN_HEREDOC || tmp->mode == TOKEN_REDIR_APPEND || tmp->mode == TOKEN_REDIR_IN )&& !(tmp->is_visited))
// 	{
// 		tmp->is_visited = 1;
// 		*node = c_node_arbre(tmp);
// 		(*node)->left = c_node_arbre(tmp->prev);
// 		(*node)->right = c_node_arbre(tmp->next);
// 		search_redir_right(tmp->next, &(*node)->right,n);
// 	}
// 	else
// 		search_redir_right(tmp->next, node,n);
// }

// void	search_pipe_left(t_node	*tmp, t_node_arbre **node, int *n)
// {
// 	if (!tmp)
// 		return ;
// 	if (tmp->mode == TOKEN_PIPE && !(tmp->is_visited))
// 	{
// 		(*n)++;
// 		tmp->is_visited = 1;
// 		*node = c_node_arbre(tmp);
// 		(*node)->left = c_node_arbre(tmp->prev);
// 		(*node)->right = c_node_arbre(tmp->next);
// 		search_redir_left(tmp, &(*node)->left, n);
// 		search_pipe_left(tmp->prev, &(*node)->left, n);
// 	}
// 	else
// 		search_pipe_left(tmp->prev, node,n);
// }

// void	search_pipe_right(t_node	*tmp, t_node_arbre **node,int *n)
// {
// 	if (!tmp)
// 		return ;
// 	if (tmp->mode == TOKEN_PIPE && !(tmp->is_visited))
// 	{
// 		(*n)++;
// 		*node = c_node_arbre(tmp);
// 		(*node)->left = c_node_arbre(tmp->prev);
// 		(*node)->right = c_node_arbre(tmp->next);
// 		search_pipe_right(tmp->next, &(*node)->right,n);
// 		tmp->is_visited = 1;
// 	}
// 	else
// 		search_pipe_right(tmp->next, node,n);
// }

// void	search_or_and(t_node	*tmp, t_node_arbre **node, int *n ,t_node **node_l)
// {
// 	if (!tmp)
// 		return ;
// 	if ((tmp->mode == TOKEN_AND || tmp->mode == TOKEN_OR) && !(tmp->is_visited))
// 	{
// 		tmp->is_visited = 1;
// 		*node = c_node_arbre(tmp);
// 		(*node)->left = c_node_arbre(tmp->prev);
// 		(*node)->right = c_node_arbre(tmp->next);
// 		(*n)++;
// 		*node_l = tmp;
// 		search_pipe_right(tmp->next, &(*node)->right, n);
// 		search_pipe_left(tmp->prev, &(*node)->left, n);
// 		search_or_and(tmp->prev, &(*node)->left, n, node_l);
// 	}
// 	else
// 		search_or_and(tmp->prev, node, n,node_l);
// }

// int	plant_5(t_node *tail, t_node_arbre **racine,t_node *node)
// {
// 	int n;

// 	n = 0;
// 	search_or_and(tail, racine, &n, &node);
// 	// if (n == 0)
// 	// {
// 	// 	search_pipe_left(tail, racine, &n);// search_pipe_right(tail->list->top, racine);
// 	// 	if (n == 0)
// 	// 		search_redir_left(tail, racine, &n);
// 	// }
// 	// else
// 	// {
// 	// 	if (n == 1)
// 	// 	{
// 	// 		search_redir_right(node, &(*racine)->right,&n);
// 	// 		search_redir_left(node, &(*racine)->left, &n);
// 	// 	}
// 	// }
// 	// if (n == 0){
// 	// 	search_redir_left(list->tail,&arbre->racine, &n);}
// 	// if (n == 0)
// 	// 	arbre->racine = c_node_arbre(list->top);
// 	return (1);
// }