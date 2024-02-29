/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 23:55:37 by sel-jett          #+#    #+#             */
/*   Updated: 2024/02/28 14:57:58 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "builtins.h"
#include "../includes/minishell.h"

char	*find_pwd(t_env *cenv)
{
	char	*str;

	if (!cenv)
		return (NULL);
	while (cenv && ft_strncmp_one(cenv->key, "PWD"))
		cenv = cenv->next;
	str = ft_strjoin(cenv->key, "=");
	str = ft_strjoin(str, cenv->value);
	return (str);
}

char	*find_oldpwd(t_env *cenv)
{
	char	*str;

	while (cenv && ft_strncmp_one(cenv->key, "OLDPWD"))
		cenv = cenv->next;
	if (cenv)
	{
		str = ft_strjoin(cenv->key, "=");
		return (ft_strjoin(str, cenv->value));
	}
	return (NULL);
}

int	ft_strncmp_one(char *tmp, char *pwd)
{
	int	i;
	int	j;

	if (!ft_strlen_b(pwd) || !ft_strlen_b(tmp))
		return (1);
	j = ft_strlen_b(pwd);
	i = -1;
	while (++i < j)
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
