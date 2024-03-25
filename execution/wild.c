/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:26:25 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/25 12:53:51 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*return_wild_at_end(DIR *dir, struct dirent *dp, char *sdk, char *str)
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
					return (closedir(dir), NULL);
				sdk = ft_strjoin(sdk, " ");
				if (!sdk)
					return (closedir(dir), NULL);
			}
		}
		dp = readdir(dir);
	}
	return (closedir(dir), wild_sorting(sdk));
}

char	*return_wild_at_first(DIR *dir, struct dirent *dp, char *sdk, char *str)
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
					return (closedir(dir), NULL);
				sdk = ft_strjoin(sdk, " ");
				if (!sdk)
					return (closedir(dir), NULL);
			}
		}
		dp = readdir(dir);
	}
	return (closedir(dir), wild_sorting(sdk));
}

char	*return_wild_at_none(DIR *dir, struct dirent *dp, char *sdk)
{
	dp = readdir(dir);
	while (dp)
	{
		sdk = ft_strjoin(dp->d_name, " ");
		if (!sdk)
			return (closedir(dir), NULL);
		dp = readdir(dir);
	}
	return (closedir(dir), wild_sorting(sdk));
}

int	ft_middle_wild(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '*')
				return (i);
			i++;
		}
	}
	return (0);
}

char	*ft_execute_wild(char *str)
{
	DIR				*dir;
	struct dirent	*dp;
	int				len;
	char			*sdk;

	if (!str || ft_middle_wild(str))
		return (str);
	(1) && (sdk = "", dir = opendir("."), dp = NULL);
	if (ft_strncmp(str, ".") == 0 || only_wild(str))
		return (return_only_wild(dir, dp, sdk));
	if (!global_checker(str))
		return (str);
	len = ft_strlen_wild_end(str);
	if (!dir)
		return (perror("opendir"), NULL);
	if (ft_strlen_wild_end(str))
		return (return_wild_at_end(dir, dp, sdk, str));
	else if (ft_strlen_wild_first(str))
		return (return_wild_at_first(dir, dp, sdk, str));
	else

		return (return_wild_at_none(dir, dp, sdk));
	closedir(dir);
	return (NULL);
}
