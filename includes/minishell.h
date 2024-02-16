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
int		plant_3(char *str, t_list   *list, int *i);
int		plant_1(char *str,t_list *list,int *i);
int		    plant_2(char *str, t_list   *list, int *i);
int         spaces(char *str, t_list   *list, int *i);
int		plant_4(t_list *list);
int			check(int c);
t_node_arg	*c_node_arg(char *str);
t_list_arg	*c_list_arg();
void		add_back_arg(t_list_arg *list, t_node_arg *node);
int		add_one(char *str, t_list   *list, int *i ,int mode);
#endif
