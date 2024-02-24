/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:17:58 by amel-has          #+#    #+#             */
/*   Updated: 2024/02/24 06:12:27 by amel-has         ###   ########.fr       */
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
	// printf("mode ---> is : %d\n",tree->mode);
	// t_node *node = tree->list->top;
	// printf("--------------------->\n");
	// while (node)
	// {
	// 	printf("[%s] -> ",node->value);
	// 	node =node->next;
	// }
	// printf("\n");
	// (void)c;
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

t_node_arbre *add_commade(t_node	*tmp)
{
	t_node_arbre	*new_node;
	t_node			*node;

	new_node = c_node_arbre(tmp);
	if (!new_node)
		return (0);
	new_node->list->top = tmp;
	node = tmp;
	while (node && (node->mode == TOKEN_EXPR || node->mode == TOKEN_SPACE))
			node = node->next;
	if (node)
	{
		node = node->prev;
		node->next  = NULL;
	}
	return (new_node);
}

t_node_arbre	*parse_cmd(t_node **tmp)
{
	t_node			*node;
	t_node_arbre	*arbre_node=NULL;
	
	if ((*tmp)->mode == TOKEN_PARENTHESE)
		//
	;
	if ((*tmp)->mode == TOKEN_EXPR)
	{
		node = *tmp;
		while ((*tmp) && (*tmp)->mode == TOKEN_EXPR)
			*tmp = (*tmp)->next;
		arbre_node = add_commade(node);
		if (!arbre_node)
			return (NULL);
		// printf("[%s]------->\n",(*tmp)->prev);
		return (arbre_node);
	}
	return	(NULL);
}
 
t_node_arbre	*parse_redir(t_node **tmp)
{
	t_node_arbre	*node_left;
	t_node_arbre	*node;

	node_left = parse_cmd(tmp);
	if (!node_left)
		return (NULL);
	if (*tmp && ((*tmp)->mode == TOKEN_REDIR_APPEND || (*tmp)->mode ==
	 TOKEN_REDIR_IN || (*tmp)->mode == TOKEN_REDIR_OUT || (*tmp)->mode == TOKEN_HEREDOC))
	{
		
	// while(*tmp && ((*tmp)->mode == TOKEN_REDIR_APPEND || (*tmp)->mode ==
	// TOKEN_REDIR_IN || (*tmp)->mode == TOKEN_REDIR_OUT || (*tmp)->mode == TOKEN_HEREDOC))
	// {
		node = c_node_arbre(*tmp);
		node->list_redir = (*tmp)->list_redir;
		node->left = node_left;
		*tmp = (*tmp)->next;
		while ((*tmp) && (*tmp)->mode == TOKEN_EXPR)
			*tmp = (*tmp)->next;	
	// }
		return (node);
	}
	return (node_left);	
}

t_node_arbre	*new_node(int mode, t_node_arbre *left, t_node_arbre *right)
{
	t_node_arbre *node;

	node = my_malloc(sizeof(t_node_arbre), 1);
	node->mode = mode;
	node->left = left;
	node->right = right;
	return (node);
}

t_node_arbre *parse_pipe(t_node **tmp)
{
	t_node_arbre *node;
	
	node = parse_redir(tmp);
	if (!node)
		return (0);
	while (*tmp && (*tmp)->mode == TOKEN_PIPE)
	{
		*tmp = (*tmp)->next;
		node = new_node(TOKEN_PIPE, node,parse_redir(tmp));
	}
	return (node);
}

t_node_arbre	*parse_and_or(t_node **tmp)
{
	t_node_arbre *node;
	int 		mode;
	
	node = parse_pipe(tmp);
	while (*tmp && (((*tmp)->mode == TOKEN_OR) || ((*tmp)->mode == TOKEN_AND)))
	{
		mode = (*tmp)->mode;
		*tmp = (*tmp)->next;
		node = new_node(mode, node, parse_pipe(tmp));
	}
	return (node);
}

int	plant_5(t_node *top, t_node_arbre **racine)
{
	
	*racine = parse_and_or(&top);
	// printf("[%s]\n",top->next->value);
	print_tree(*racine,0);
	return (1);
}