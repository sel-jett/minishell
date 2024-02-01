/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 22:39:29 by sel-jett          #+#    #+#             */
/*   Updated: 2024/02/01 06:38:19 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error(void)
{
	write(2, "Error\n", 6);
	my_malloc(0, 0);
}

void	dataclear(t_data **hold)
{
	t_data	*tmp;
	t_data	*ptr;

	if (!hold || !*hold)
		return ;
	tmp = *hold;
	while (tmp)
	{
		ptr = tmp;
		tmp = tmp->next;
		free(ptr->data);
		free(ptr);
	}
	*hold = NULL;
}

void	*my_malloc(size_t size, int mode)
{
	static t_data	*head;
	t_data			*node;
	void			*data;

	if (mode == 1)
	{
		data = malloc(size);
		if (!data)
			return (dataclear(&head), exit(1), NULL);
		node = malloc(sizeof(t_data));
		if (!node)
			return (dataclear(&head), exit(1), NULL);
		node->data = data;
		node->next = NULL;
		(head) && (node->next = head);
		head = node;
		return (data);
	}
	if (!mode)
		return (dataclear(&head), exit(1), NULL);
	return (dataclear(&head), exit(0), NULL);
}
