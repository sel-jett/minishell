/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 23:55:37 by sel-jett          #+#    #+#             */
/*   Updated: 2024/02/02 00:02:53 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*find_pwd(t_env *cenv)
{
	int	i;

	i = 0;
	if (!cenv)
		return (NULL);
	while (cenv && strncmp(cenv->data, "PWD", 3))
		cenv = cenv->next;
	return (cenv->data);
}

char	*find_oldpwd(t_env *cenv)
{
	int		i;

	i = 0;
	while (cenv && strncmp(cenv->data, "OLDPWD", 6))
		cenv = cenv->next;
	if (cenv)
		return (cenv->data);
	return (NULL);
}

int	ft_strncmp_one(char *tmp, char *pwd)
{
	int	i;

	i = -1;
	while (++i < 3)
		if (tmp[i] != pwd[i])
			return (1);
	return (0);
}

int	ft_strncmp_two(char *tmp, char *pwd)
{
	int	i;

	i = -1;
	while (++i < 6)
		if (tmp[i] != pwd[i])
			return (1);
	return (0);
}

char	*pwd_joiner(char *temp_old, char *temp, char *path)
{
	temp = ft_strjoin("PWD", (temp_old + 6));
	temp = ft_strjoin(temp, "/");
	temp = ft_strjoin(temp, (char *)path);
	return (temp);
}
