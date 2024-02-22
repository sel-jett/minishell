/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:17:58 by amel-has          #+#    #+#             */
/*   Updated: 2024/02/22 07:07:21 by amel-has         ###   ########.fr       */
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

void	search_pipe_left(t_node	*tmp, t_node_arbre **node)
{
	if (!tmp)
		return ;
	if (tmp->mode == TOKEN_PIPE && !(tmp->is_visited))
	{
		*node = c_node_arbre(tmp);
		search_pipe_left(tmp->next,&(*node)->right);
		tmp->is_visited = 1;
	}
	else
		search_pipe_left(tmp->next, node);
}

void	search_pipe_right(t_node	*tmp, t_node_arbre **node)
{
	if (!tmp)
		return ;
	if (tmp->mode == TOKEN_PIPE && !(tmp->is_visited))
	{
		*node = c_node_arbre(tmp);
		search_pipe_right(tmp->prev, &(*node)->right);
		tmp->is_visited = 1;
	}
	else
		search_pipe_right(tmp->prev, node);
}

void affiche_arbre(t_node_arbre *node,int x,int prof)
{
    for (int i=0; i < prof; i++)
    {
        fputs("     ", stdout);
    }
	if (!node)
		return ;
	if (x == -1)
		printf("                 racine --> [ %s ]\n",node->value);
	if (x == 0)
		printf("left --> [ %s ]        ", node->value);
	else if (x == 1)
		printf("right --> [ %s ] \n", node->value);
	affiche_arbre(node->left,0,prof + 1);
	affiche_arbre(node->right,1,prof+1);
}

void	search_or_and(t_node	*tmp, t_node_arbre **node)
{
	if (!tmp)
		return ;
	if ((tmp->mode == TOKEN_AND || tmp->mode == TOKEN_OR))
	{
		*node = c_node_arbre(tmp);
		search_pipe_right(tmp->next,&(*node)->right);
		search_pipe_left(tmp->prev,&(*node)->left);
		search_or_and(tmp->prev, &(*node)->left);
	}
	else{
		search_or_and(tmp->prev, node);
		// if (tmp->next && (*node)->left)
		// 	search_pipe(tmp->next,&(*node)->left);
	}
}

int	plant_5(t_list *list)
{
	t_arbre			*arbre;

	arbre = c_arbre();
	if (!arbre)
		return (0);
	// arbre->racine = c_node_arbre(list->top);
	// printf("%s\n",list->tail->prev->value);
	search_or_and(list->tail, &arbre->racine);
	// printf("[%s]\n",arbre->racine->left->value);
	affiche_arbre(arbre->racine,-1,0);
	return (1);
}