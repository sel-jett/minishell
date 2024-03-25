/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:04:03 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/25 21:02:37 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_alpha_3(char c)
{
	if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
		|| c == '_' || (c >= '0' && c <= '9')))
		return (0);
	return (1);
}

void	ft_env(t_env *tmp)
{
	if (!get_path(tmp))
	{
		ft_printf("minishell: env", NULL);
		ft_printf(": command not found\n", NULL);
		ft_status(127, 1);
		return ;
	}
	while (tmp)
	{
		if (tmp->key)
		{
			printf("%s", tmp->key);
			printf("=");
			printf("%s\n", tmp->value);
		}
		else if (tmp->value)
		{
			printf("=%s\n", tmp->value);
		}
		tmp = tmp->next;
	}
	ft_status(0, 1);
}

int	check_key(char *key)
{
	int	i;

	i = 0;
	if (!key)
		return (0);
	if (key[i] != '_' && !is_alpha(key[i]))
		return (0);
	i++;
	while (key[i])
	{
		if (key[i] != '_' && !is_alpha(key[i]) && !is_num(key[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*cd_init(t_env **cenv, t_env **exp, char *pwd)
{
	char	*temp_old;

	if (value_key(*cenv, "PWD"))
		pwd = value_key(*cenv, "PWD");
	else if (!pwd)
	{
		ft_printf("minishell: cd: PWD not set\n", NULL);
		ft_status(1, 1);
		return (NULL);
	}
	temp_old = find_oldpwd(*exp);
	ft_list_remove_if(exp, "PWD", ft_strncmp_one);
	ft_list_remove_if(cenv, "OLDPWD", ft_strncmp_one);
	ft_list_remove_if(exp, "OLDPWD", ft_strncmp_one);
	return (ft_strjoin("OLDPWD=", ft_strdup(pwd)));
}

char	*find_pwd(t_env *cenv)
{
	char	*str;

	if (!cenv)
		cenv = cenv->next;
	while (cenv && ft_strncmp_one(cenv->key, "PWD"))
		cenv = cenv->next;
	if (!cenv)
		return (NULL);
	str = ft_strjoin(cenv->key, "=");
	str = ft_strjoin(str, cenv->value);
	if (!str)
		return (getcwd(0, 0));
	return (str);
}
