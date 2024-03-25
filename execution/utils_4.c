/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:17:09 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/25 18:20:20 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**env_to_arr(t_env *env)
{
	t_env	*tmp;
	char	**arr;
	int		i;

	(1) && (tmp = env, i = 0);
	while (tmp)
		(1) && (i++, tmp = tmp->next);
	arr = my_malloc(sizeof(char *) * (i + 1), 1);
	if (!arr)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		arr[i] = ft_strjoin(tmp->key, "=");
		if (!arr[i])
			return (NULL);
		arr[i] = ft_strjoin(arr[i], tmp->value);
		if (!arr[i])
			return (NULL);
		i++;
		tmp = tmp->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	ft_print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		dprintf(2, "\"%s\"\n", arr[i]);
		i++;
	}
}

int	liked_size(t_node *tree)
{
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = tree;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	*return_only_wild(DIR *dir, struct dirent *dp, char *sdk)
{
	dp = readdir(dir);
	while (dp)
	{
		if ((dp->d_name)[0] != '.')
		{
			sdk = ft_strjoin(sdk, dp->d_name);
			if (!sdk)
				return (closedir(dir), NULL);
			sdk = ft_strjoin(sdk, " ");
			if (!sdk)
				return (closedir(dir), NULL);
		}
		dp = readdir(dir);
	}
	return (closedir(dir), wild_sorting(sdk));
}