/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:58:34 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/26 10:33:52 by sel-jett         ###   ########.fr       */
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
	if (!str || !s)
		return (0);
	while (str[i] && str[i] == '*')
		i++;
	if (!(str + i))
		return (0);
	len = (unsigned long)ft_strlen_b(str + i);
	while ((s + j) && (unsigned long)ft_strlen_b(s + j) != len)
		j++;
	return (j);
}

int	only_wild(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != '*')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_wild_joiner(char **ptr3)
{
	char	*ktr;

	ktr = NULL;
	while (ptr3 && *ptr3)
	{
		ktr = ft_strjoin(ktr, *ptr3);
		if (!ktr)
			return (NULL);
		if ((*ptr3 + 1))
			ktr = ft_strjoin_char(ktr, -32);
		ptr3++;
	}
	return (ktr);
}

char	*wild_sorting(char *str)
{
	char	**ptr;
	char	**ptr2;
	char	**ptr3;
	char	*tmp;
	int		i;

	if (!str)
		return (NULL);
	(1) && (ptr = ft_split(str, -32), ptr3 = ptr);
	while (*ptr)
	{
		(1) && (ptr2 = ptr, i = 0);
		while (*(ptr2 + 1))
		{
			if (ft_cmp(*ptr2, *(ptr2 + 1)) > 0)
			{
				(1) && (tmp = *(ptr2), *(ptr2) = *(ptr2 + 1));
				(1) && (*(ptr2 + 1) = tmp, ptr = ptr3, i = 1);
			}
			ptr2++;
		}
		if (i == 0)
			ptr++;
	}
	return (ft_wild_joiner(ptr3));
}
