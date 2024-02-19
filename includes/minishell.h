/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:48:58 by amel-has          #+#    #+#             */
/*   Updated: 2024/02/19 05:18:28 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include "structs.h"
# include <unistd.h>
# include <readline/readline.h>
# include <stdbool.h>

t_list		    *c_list(void);
t_list_arg	    *c_list_arg(void);
t_list_redir    *c_list_redir(void);
t_node		    *c_node(char *str, t_node *tail, int mode);
t_node_arg	    *c_node_arg(char *str);
t_node_redir    *c_node_redir(char *str);
void            add_back_redir(t_list_redir *list, t_node_redir *node);
int			    plants(t_list *list, int *i);
void		    *my_malloc(size_t size, int mode);
void		    add_back(t_list *list, t_node *node);
int			    plant_3(t_list *list, int *i);
int			    plant_1(t_list *list, int *i);
int			    plant_2(t_list *list, int *i);
int			    spaces(t_list *list, int *i);
int			    plant_4(t_list *list);
int			    check(int c);
int				is_empty(char *str);
void		    add_back_arg(t_list_arg *list, t_node_arg *node);
int			    add_one(t_list	*list, int *i, int mode);
int				add_list_redir(t_node *tmp);
#endif
