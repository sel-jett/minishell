/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 23:28:22 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/13 22:10:32 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_arbre	*c_arbre(void)
{
	t_arbre	*new_arbre;

	new_arbre = my_malloc(sizeof(t_arbre), 1);
	if (!new_arbre)
		return (0);
	new_arbre->racine = 0;
	return (new_arbre);
}

t_node_arbre	*c_node_arbre(t_node *node)
{
	t_node_arbre	*new_node_arbre;

	if (!node)
		return (NULL);
	new_node_arbre = my_malloc(sizeof(t_node_arbre), 1);
	if (!new_node_arbre)
		return (0);
	new_node_arbre->list = NULL;
	new_node_arbre->list_redir = NULL;
	new_node_arbre->list = NULL;
	new_node_arbre->value = node->value;
	new_node_arbre->mode = node->mode;
	new_node_arbre->left = NULL;
	new_node_arbre->right = NULL;
	new_node_arbre->flag_expend = node->flag_expend;
	new_node_arbre->flag_space = node->flag_space;
	return (new_node_arbre);
}
