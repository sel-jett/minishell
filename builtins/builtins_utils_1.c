/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:39:32 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/25 16:39:44 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_print(char *str)
{
	ft_printf("exit\n", NULL);
	ft_printf("minishell: exit: ", str);
	ft_printf(": numeric argument required", NULL);
	ft_printf("\n", NULL);
}
