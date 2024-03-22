/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:26:25 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/22 08:49:56 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	length(char *s, char *str)
{
	int				j;
	int				i;
	unsigned long	len;

	j = 0;
	i = 0;
	while (str[i] && str[i] == '*')
		i++;
	len = strlen(str + i);
	while (strlen(s + j) != len)
		j++;
	return (j);
}

int	only_wild(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '*')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_execute_wild(char *str)
{
	DIR				*dir;
	struct dirent	*dp;
	int				len;
	char			*sdk;

	sdk = "";
	dir = opendir(".");
	if (ft_strncmp(str, ".") == 0 || only_wild(str))
	{
		dp = readdir(dir);
		while (dp)
		{
			if ((dp->d_name)[0] != '.')
			{
				sdk = ft_strjoin(sdk, dp->d_name);
				if (!sdk)
					return (NULL);
				sdk = ft_strjoin(sdk, " ");
				if (!sdk)
					return (NULL);
			}
			dp = readdir(dir);
		}
		return (sdk);
	}
	if (!global_checker(str))
	{
		return (str);
	}
	len = ft_strlen_wild_end(str);
	if (!dir)
		return (perror("opendir"), NULL);
	if (ft_strlen_wild_end(str))
	{
		dp = readdir(dir);
		while (dp)
		{
			if (!ft_strncmp_wild(dp->d_name, str, ft_strlen_wild_end(str)))
			{
				if ((dp->d_name)[0] != '.')
				{
					sdk = ft_strjoin(sdk, dp->d_name);
					if (!sdk)
						return (NULL);
					sdk = ft_strjoin(sdk, " ");
					if (!sdk)
						return (NULL);
				}
			}
			dp = readdir(dir);
		}
		return (sdk);
	}
	else if (ft_strlen_wild_first(str))
	{
		dp = readdir(dir);
		while (dp)
		{
			if (!ft_strncmp((dp->d_name + length(dp->d_name, str)), str + 1))
			{
				if ((dp->d_name)[0] != '.')
				{
					sdk = ft_strjoin(sdk, dp->d_name);
					if (!sdk)
						return (NULL);
					sdk = ft_strjoin(sdk, " ");
					if (!sdk)
						return (NULL);
				}
			}
			dp = readdir(dir);
		}
		return (sdk);
	}
	else
	{
		dp = readdir(dir);
		while (dp)
		{
			sdk = ft_strjoin(dp->d_name, " ");
			if (!sdk)
				return (NULL);
			dp = readdir(dir);
		}
		return (sdk);
	}
	closedir(dir);
	return (NULL);
}
