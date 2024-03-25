/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 06:25:17 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/24 20:13:18 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static int	count_words(char const *str, char c)
{
	int	index;
	int	count;
	int	i;

	count = 0;
	index = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			index = 0;
		else if (index == 0)
		{
			count++;
			index = 1;
		}
		i++;
	}
	return (count);
}

static char	*get_word(const char *s, char c)
{
	char	*word;
	size_t	len;
	size_t	i;

	i = -1;
	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = (char *)malloc(len + 1);
	if (!word)
		return (0);
	while ((++i) < len)
		word[i] = s[i];
	word[len] = '\0';
	return (word);
}

static void	*ft_free(char **arr, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(arr[i++]);
	free(arr);
	return (0);
}

char	**ft_split(const char *s, char c)
{
	char	**str;
	int		i;

	i = 0;
	if (!s)
		return (0);
	str = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!str)
		return (0);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			str[i] = get_word(s, c);
			if (!str[i])
				return (ft_free(str, i));
			while (*s && *s != c)
				s++;
			i++;
		}
	}
	str[i] = 0;
	return (str);
}

int	ft_strncmp_lfassi(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
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

int	ft_strlen_b(const char *str)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		size;
	char	*str;
	int		i;

	size = ft_strlen_b(s1) + ft_strlen_b(s2);
	str = malloc(size + 1);
	i = 0;
	size = 0;
	while (s1 && s1[i])
		(1) && (str[i] = s1[i], i++);
	while (s2 && s2[size])
		(1) && (str[i + size] = s2[size], size++);
	str[i + size] = '\0';
	return (str);
}


