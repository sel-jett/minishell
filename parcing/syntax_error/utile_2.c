/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:17:58 by amel-has          #+#    #+#             */
/*   Updated: 2024/02/19 00:04:55 by amel-has         ###   ########.fr       */
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