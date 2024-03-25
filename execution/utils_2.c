/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:10:14 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/25 01:18:45 by sel-jett         ###   ########.fr       */
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

void	count_joyner(char **str, int *len)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j] != '\\' && str[i][j])
		{
			(*len)++;
			j++;
		}
		if (str[i][j] != '\\')
			(*len)++;
		i++;
	}
}

static int	count_words(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			i++;
			continue ;
		}
		count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static	char	**ft_fill_str_2(char **str, char const *s, char c)
{
	int	i;
	int	pos;
	int	calc;

	i = 0;
	pos = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			continue ;
		}
		calc = i;
		while (s[i] && s[i] != c)
			i++;
		str[pos] = my_malloc((i - calc + 1), 1);
		if (!str[pos])
			return (NULL);
		ft_strlcpy(str[pos], (s + calc), (i - calc + 1));
		pos++;
	}
	str[pos] = NULL;
	return (str);
}

char	**ft_split_2(char const *s, char c)
{
	int		words;
	char	**str;

	if (!s)
		return (0);
	words = count_words(s, c);
	str = my_malloc((sizeof(char *) * (words + 1)), 1);
	if (!str)
		return (NULL);
	if (!ft_fill_str_2(str, s, c))
		return (NULL);
	return (str);
}

char	**joyner(char **str)
{
	int		i;
	int		j;
	int		len;
	int		k;
	char	*str_r;

	(1) && (i = 0, j = 0, len = 0, k = 0);
	count_joyner(str, &len);
	str_r = my_malloc((sizeof(char) * (len + 1)), 1);
	if (!str_r)
		return (0);
	while (str[i])
	{
		// dprintf(2, "str[%d] = %s\n", i, str[i]);
		j = 0;
		while (str[i][j] != '\\' && str[i][j])
		{
			str_r[k] = str[i][j];
			(1) && (k++, j++);
		}
		if (str[i][j] != '\\')
			str_r[k++] = -32;
		i++;
	}
	str_r[k] = '\0';
	// dprintf(2, "str_r = %s\n", str_r);
	// ft_print_arr(str_r);
	return (ft_split_2(str_r, -32));
}
