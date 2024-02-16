#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include "structs.h"
# include <unistd.h>
# include <readline/readline.h>
# include <stdbool.h>

t_node		*c_node(char *str, t_node *tail, int mode);
t_list		*c_list();
void		*my_malloc(size_t size, int mode);
void		add_back(t_list *list,t_node *node);
void		plant_3(char *str, t_list   *list, int *i);
void		plant_1(char *str,t_list *list,int *i);
void		plant_2(char *str, t_list   *list, int *i);
void		spaces(char *str, t_list   *list, int *i);
bool		plant_4(t_list *list);
int			check(int c);
t_node_arg	*c_node_arg(char *str);
t_list_arg	*c_list_arg();
void		add_back_arg(t_list_arg *list, t_node_arg *node);
#endif
