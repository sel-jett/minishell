/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:13:37 by sel-jett          #+#    #+#             */
/*   Updated: 2024/02/29 13:22:56 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_execute_or(t_node_arbre *tree, t_env *e)
{
	execute(tree->left, e);
	if (ft_status(0, 0))
		execute(tree->right, e);
}
