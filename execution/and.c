/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:09:42 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/20 04:04:47 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_execute_and(t_node_arbre *tree, t_env *e, t_env *exp)
{
	
	execute(tree->left, e, exp);
	// dprintf(2, "status: %d\n", ft_status(0, 0));
	if (ft_status(0, 0) == 0)
	{
		// while (tree->right->list->top)
		// {
		// 	tree->right->list->top = tree->right->list->top->next;
		// }
		// exit(0);
		execute(tree->right, e, exp);
		// exit(1);
	}
}
