/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 23:28:22 by amel-has          #+#    #+#             */
/*   Updated: 2024/02/24 23:32:51 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_arbre    *c_arbre()
{
    t_arbre *new_arbre;

    new_arbre = my_malloc(sizeof(t_arbre), 1);
    if(!new_arbre)
        return (0);
    new_arbre->racine = 0;
    return (new_arbre);
}

t_node_arbre    *c_node_arbre(t_node    *node)
{
    if(!node)
        return (NULL);
    t_node_arbre *new_node_arbre;
    new_node_arbre = my_malloc(sizeof(t_node_arbre), 1);
    if (!new_node_arbre)
        return (0);
    new_node_arbre->list = c_list();
    new_node_arbre->list_redir = c_nlist();
    new_node_arbre->value = node->value;
    new_node_arbre->mode = node->mode;
    new_node_arbre->left = NULL;
    new_node_arbre->right = NULL;
    new_node_arbre->flag_expend = 0;
	new_node_arbre->flag_expend = 0;
    return (new_node_arbre);
}
