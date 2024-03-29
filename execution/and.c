/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:09:42 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/22 07:10:07 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_execute_and(t_node_arbre *tree, t_env *e, t_env *exp)
{
	execute(tree->left, e, exp);
	if (ft_status(0, 0) == 0)
		execute(tree->right, e, exp);
}
