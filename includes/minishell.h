/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:48:58 by amel-has          #+#    #+#             */
/*   Updated: 2024/02/27 09:34:49 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include "structs.h"
# include <unistd.h>
# include <signal.h>
# include "/Users/amel-has/.brew/opt/readline/include/readline/readline.h"
# include "/Users/amel-has/.brew/opt/readline/include/readline/history.h"
# include <stdbool.h>

t_node_arbre	*parse_and_or(t_node **tmp);
t_node			*c_cpynode(t_node *node,t_node *tail,t_list *list);
t_nlist         *c_nlist(void);
t_nnode         *c_nnode(char *str);
void            add_nback(t_nlist *list, t_nnode *node);
void            affiche(t_list *list);
int				add_args(t_nlist *list, char *str, int *i);
int				check_syntax_1(t_node *tmp);
int				check_syntax_2(t_node *tmp);
int				check_syntax_3(t_node *tmp);
int				check_syntax_4(t_node *tmp);
t_node_arbre	*add_commade(t_node	*tmp);
int				add_list_redir(t_node *node);
void			print_tree(t_node_arbre    *tree, int c);
t_arbre			*c_arbre(void);
t_node_arbre	*c_node_arbre(t_node *node);
t_list			*c_list(void);
t_node			*c_node(char *str, t_node *tail, int mode, t_list *list);
int			    plants(t_list *list, int *i);
void			*my_malloc(size_t size, int mode);
void			add_back(t_list *list, t_node *node);
int				plant_3(t_list *list, int *i);
int				plant_1(t_list *list, int *i);
int				plant_2(t_list *list, int *i);
int				spaces(t_list *list, int *i);
int				plant_4(t_list *list);
int				check(int c);
int				is_empty(char *str);
int				add_one(t_list	*list, int *i, int mode);
int				add_list_redir(t_node *tmp);
int				plant_6(t_node *top, t_node_arbre **racine);
#endif
