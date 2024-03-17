/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:09:42 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/17 01:01:31 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_execute_and(t_node_arbre *tree, t_env *e, t_env *exp)
{
	
	execute(tree->left, e, exp);
	// dprintf(2, "status: %d\n", ft_status(0, 0));
	if (!ft_status(0, 0))
	{
		// while (tree->right->list->top)
		// {
		// 	dprintf(2, "waaa: %s\n", tree->right->list->top->value);
		// 	tree->right->list->top = tree->right->list->top->next;
		// }
		execute(tree->right, e, exp);
		// exit(1);
	}
}
