/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:09:39 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/26 03:31:20 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strlen_bi(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**ft_func_string(char **str, int i)
{
	char	**tmp;
	int		len;
	int		j;

	len = ft_strlen_bi(str);
	tmp = my_malloc((len * 8), 1);
	if (!tmp)
		return (NULL);
	len = 0;
	j = 0;
	while (str[len])
	{
		if (i == len)
		{
			len += 1;
			continue ;
		}
		tmp[j] = str[len];
		len++;
		j++;
	}
	tmp[j] = NULL;
	return (tmp);
}

char	**array_structer(char **str)
{
	int	tab[2];

	(1) && (tab[0] = 0, tab[1] = 0);
	while (str && str[tab[0]] && str[tab[0]][0])
	{
		while (str[tab[0]][tab[1]])
		{
			if (str[tab[0]][0] == '\\')
			{
				if (str[tab[0] + 1])
				{
					(1) && (str = ft_func_string(str, tab[0]), tab[0] = 0);
					continue ;
				}
				else
				{
					str[tab[0]] = NULL;
					break ;
				}
			}
			tab[1]++;
		}
		(1) && (tab[1] = 0, tab[0]++);
	}
	return (str = joyner(str), str);
}

int	array_checker(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '\v' || str[i][j] == '\\' || str[i][j] == -32)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_strlen_tri(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char **array_31(char **str)
{
	int	i;
	int	j;
	int	len;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = my_malloc((ft_strlen_tri(str) * 8), 1);
	while (str[i])
	{
		tmp[i] = NULL;
		j = 0;
		len = 0;
		while (str[i][j])
		{
			if (str[i][j] == -31)
			{
				j++;
				continue ;
			}
			tmp[i] = ft_strjoin_char(tmp[i], str[i][j]);
			j++;
		}
		tmp[i] = ft_strjoin_char(tmp[i], '\0');
		i++;
	}
	tmp[i] = NULL;
	// ft_print_arr(tmp);
	return (tmp);
}

// static int	count_words(char const *str, char c)
// {
// 	int	index;
// 	int	count;
// 	int	i;

// 	count = 0;
// 	index = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == c)
// 			index = 0;
// 		else if (index == 0)
// 		{
// 			count++;
// 			index = 1;
// 		}
// 		i++;
// 	}
// 	return (count);
// }

// static char	*get_word(const char *s, char c)
// {
// 	char	*word;
// 	size_t	len;
// 	size_t	i;

// 	i = -1;
// 	len = 0;
// 	while (s[len] && s[len] != c)
// 		len++;
// 	word = (char *)malloc(len + 1);
// 	if (!word)
// 		return (0);
// 	while ((++i) < len)
// 		word[i] = s[i];
// 	word[len] = '\0';
// 	return (word);
// }



void c(char **str, int *len)
{
	int		i;
	int		j;
	char	**s;

	i = 0;
	while (str[i])
	{
		if (str[i][ft_strlen_b(str[i]) - 1] == -31)
		{
			j = 0;
			s =  ft_split(str[i], ' ');
			while (s[j])
			{
				 (*len)++;
				 j++;
			}
		}
		(*len)++;
		i++;
	}
}

char **f(char **str, int i, int j, int k)
{
	int		len;
	char	**s;
	char	**str_r;

	(1) && (len = 0, c(str, &len), 0);
	str_r = my_malloc((sizeof(char *) * (len + 1)), 1);
	if (!str_r)
		return (0);
	while (str[i])
	{
		if (str[i][ft_strlen_b(str[i]) - 1] == -31)
		{
			j = 0;
			s =  ft_split(str[i], ' ');
			while (s[j])
			{
				 str_r[k] = ft_strdup(s[j]);
				 (1) && (j++, k++);
			}
		}
		else
			str_r[k++] = strdup(str[i]);
		i++;
	}
	return (str_r[k] = NULL, str_r);
}

void change(char **str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i][ft_strlen(str[i]) - 1] == -31)
			str[i][strlen(str[i]) - 1] = '\0';
		i++;
	}
}

void	ft_execute_cmd(t_node_arbre *tree, t_env **env, t_env **exp)
{
	char			**cmmd;
	char			**path;
	t_node			*tmp;
	t_node			*smp;
	int				check;
	int	i, j ,k;

	(1) && (i = 0, j = 0, k = 0);
	(1) && (tmp = tree->list->top, smp = tree->list->top, check = 0);
	path = ft_split(get_path(*env), ':');
	cmmd = linkedlist_to_arr(tmp, *exp);
	// ft_print_arr(cmmd);
	// return ;
	if (!cmmd)
		return ;
	// ft_print_arr(cmmd);
	flag_to_expand(smp, cmmd, &check, exp);
	if (!dup_wild(cmmd, tree->list->top, &check))
		return ;
	if (!execute_cmd_child(check, &cmmd))
		return ;
	backslach_filler(cmmd);
	if (array_checker(cmmd))
		cmmd = array_structer(cmmd);
	if (is_builtin(cmmd[0]))
	{
		ft_builtin(array_31(cmmd), env, exp);
		return ;
	}
	// ft_print_arr(array_31(f(cmmd, i, j, k)));
	ft_execute_child(env_to_arr(*env), array_31(f(cmmd, i, j, k)), path);
}
