/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 23:18:52 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/25 20:52:23 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_setter(char *temp, t_env **cenv, t_env **exp, t_env *tmp)
{
	tmp = env_new(temp, *cenv);
	if (!tmp)
		return ;
	ft_lstadd_back(cenv, tmp);
	tmp = env_new(temp, *exp);
	if (!tmp)
		return ;
	ft_lstadd_back(exp, env_new(temp, *exp));
}

void	cd_applier(t_env **cenv, t_env **exp, char *b, const char **path)
{
	char	*temp;
	char	*temp_old;
	t_env	*tmp;
	int		i;

	temp = NULL;
	temp_old = cd_init(cenv, exp, b);
	if (!temp_old)
		return ;
	if (!getcwd(b, PATH_MAX))
		(1) && (i = 0, cd_second(), 0);
	else
		i = 1;
	tmp = env_new(temp_old, *cenv);
	if (!tmp)
		return ;
	ft_lstadd_back(cenv, tmp);
	tmp = env_new(temp_old, *exp);
	if (!tmp)
		return ;
	temp = path_getter(temp, *cenv, i, path);
	ft_lstadd_back(exp, tmp);
	cd_setter(temp, cenv, exp, tmp);
}

void	cd_application(t_env **cenv, t_env **exp, char *b, const char **path)
{
	getcwd(b, PATH_MAX);
	if (cd_error(path[0]))
		return ;
	cd_applier(cenv, exp, b, path);
}

int	cd_home_check(const char **path, t_env *cenv)
{
	if ((!path[0] || !path[0][0]) && (!value_key(cenv, "HOME") || \
		!(value_key(cenv, "HOME"))[0]))
	{
		ft_status(0, 0);
		return (0);
	}
	path[0] = value_key(cenv, "HOME");
	if (!path[0])
	{
		ft_printf("minishell: cd: HOME not set\n", NULL);
		ft_status(1, 1);
		return (0);
	}
	return (1);
}

void	cd(const char **path, t_env **cenv, t_env **exp)
{
	char	*b;

	b = my_malloc(PATH_MAX + 1, 1);
	if (!path[0] || !path[0][0] || !ft_strncmp((char *)path[0], "~") || \
		!ft_strncmp((char *)path[0], "--"))
	{
		if (!cd_home_check(path, *cenv))
			return ;
	}
	else if (!ft_strncmp((char *)path[0], "-"))
	{
		path[0] = value_key(*cenv, "OLDPWD");
		if (!path[0])
		{
			ft_printf("minishell: cd: OLDPWD not set\n", NULL);
			ft_status(1, 1);
			return ;
		}
	}
	cd_application(cenv, exp, b, path);
}
