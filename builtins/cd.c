/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 23:18:52 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/24 13:10:31 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cd_init(t_env **cenv, t_env **exp)
{
	char	*pwd;
	char	*temp_old;

	pwd = getcwd(0, 0);
	if (!pwd)
	{
		ft_printf("minishell: cd: PWD not set\n", NULL);
		ft_status(1, 1);
		return (NULL);
	}
	temp_old = find_oldpwd(*exp);
	ft_list_remove_if(cenv, "PWD", ft_strncmp_one);
	ft_list_remove_if(exp, "PWD", ft_strncmp_one);
	ft_list_remove_if(cenv, "OLDPWD", ft_strncmp_one);
	ft_list_remove_if(exp, "OLDPWD", ft_strncmp_one);
	return (ft_strjoin("OLD", ft_strdup(pwd)));
}

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

	temp = NULL;
	temp_old = cd_init(cenv, exp);
	if (!temp_old)
		return ;
	tmp = env_new(temp_old, *cenv);
	if (!tmp)
		return ;
	ft_lstadd_back(cenv, tmp);
	tmp = env_new(temp_old, *cenv);
	if (!tmp)
		return ;
	ft_lstadd_back(exp, tmp);
	temp = path_getter(temp, temp_old, b, path);
	cd_setter(temp, cenv, exp, tmp);
}

void	cd_application(t_env **cenv, t_env **exp, char *b, const char **path)
{
	if (cd_error(path[0]))
		return ;
	else if (!getcwd(b, PATH_MAX))
		cd_second();
	cd_applier(cenv, exp, b, path);
}

void	cd(const char **path, t_env **cenv, t_env **exp)
{
	char	*b;

	b = my_malloc(PATH_MAX + 1, 1);
	if (!path[0] || !ft_strncmp((char *)path[0], "~") || \
		!ft_strncmp((char *)path[0], "--"))
	{
		path[0] = value_key(*cenv, "HOME");
		if (!path[0])
		{
			ft_printf("minishell: cd: HOME not set\n", NULL);
			ft_status(1, 1);
			return ;
		}
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
