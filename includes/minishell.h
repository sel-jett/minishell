/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:48:58 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/16 05:24:13 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include "structs.h"
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
 #include <fcntl.h>
// # include "/Users/amel-has/.brew/opt/readline/include/readline/readline.h"
// # include "/Users/amel-has/.brew/opt/readline/include/readline/history.h"
// void			print_tree(t_node_arbre    *tree, int c);
// void            affiche(t_list *list);
int             plant_5(t_node	*tmp, t_list *list);
int             add_args(t_nlist *list, char *str, int *i);
void            affichage(int n);
int				ft_status(int status, bool mode);
void			check_wilc(t_node *node);
bool			is_spaces(char c);
bool			is_text(t_node *tmp);
bool			is_redir(t_node *tmp);
t_node_arbre	*parse_and_or(t_node **tmp);
t_node_arbre	*parse_pipe(t_node **tmp);
t_node_arbre	*parse_redir(t_node **tmp);
t_node_arbre	*parse_cmd(t_node **tmp);
t_node_arbre	*parse_parenthese(t_node **tmp);
t_node_arbre	*new_sub(t_node_arbre *racine);
t_node_arbre	*new_node(int mode, t_node_arbre *left, t_node_arbre *right);
t_node			*c_cpynode(t_node *node, t_node *tail, t_list *list);
t_nlist			*c_nlist(void);
t_nnode			*c_nnode(t_node *node);
void			add_nback(t_nlist *list, t_nnode *node);
int				add_args(t_nlist *list, char *str, int *i);
int				check_syntax_1(t_node *tmp);
int				check_syntax_2(t_node *tmp);
int				check_syntax_3(t_node *tmp);
int				check_syntax_4(t_node *tmp);
t_node_arbre	*add_commade(t_node	*tmp);
int				add_list_redir(t_node *node);
void			print_tree(t_node_arbre *root);
t_arbre			*c_arbre(void);
t_node_arbre	*c_node_arbre(t_node *node);
t_list			*c_list(void);
t_node			*c_node(char *str, t_node *tail, int mode, t_list *list);
int				plants(t_list *list, int *i);
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
///////////////////////// EXECUTION //////////////////////////

char			*ft_handler(char **cmmd, char **path);
void			ft_execute_child(char **envp, char **cmmd, char **path);
int				ft_status(int status, bool mode);
void			execute(t_node_arbre *tree, t_env *e, t_env *exp);
void			ft_execute_cmd(t_node_arbre *tree, t_env **env, t_env **exp);
void			ft_execute_pipe(t_node_arbre *tree, t_env *e, t_env *exp);
void			ft_execute_and(t_node_arbre *tree, t_env *e, t_env *exp);
void			ft_execute_or(t_node_arbre *tree, t_env *e, t_env *exp);
void			ft_execute_subshell(t_node_arbre *tree, t_env *e, t_env *exp);
void			ft_execute_redir_out(t_node_arbre *tree, t_env	*env, t_env *exp);
// void			ft_execute_redir_in(t_node_arbre *tree, t_env *env, t_env *exp);
void			ft_printf(const char *str, const char *str2);
void			ft_execve(char *env_var, char **env, char **cmmd);
char			**env_to_arr(t_env *env);
void			ft_print_arr(char **arr);
int				liked_size(t_node *tree);
char			**linkedlist_to_arr(t_node *tree);
char			*get_path(t_env *env);

///////////////////////// BUILTINS //////////////////////////

bool			is_builtin(char *cmd);
int				ft_strlen_b(const char *str);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
char			**ft_split(char const *s, char c);
char			*get_key(char *data);
char			*get_value(char *data);
char			*value_key(t_env *tmp, char *key);
char			*pwd_joiner(char *temp_old, char *temp, char *path);
t_env			*env_new(char *data, t_env *tmp);
int				ft_strncmp_one(char *tmp, char *pwd);
int				ft_strncmp_two(char *tmp, char *pwd);
t_env			*ft_env_parser(char **env);
char			*find_pwd(t_env *cenv);
char			*ft_strtrim(char *cmd);
int				check_first(char *cmd);
char			*find_oldpwd(t_env *cenv);
t_env			*ft_lstlast(t_env *lst);
void			ft_list_remove_if(t_env **begin_list, void *data_ref, int (*cmp)());
char			*ft_strdup(char *s);
void			ft_fpintf(const char *msg);
char			*ft_strjoin(char *s1, char *s2);
void			echo(const char **path, int mode);
void			ft_unset(char **cmd, t_env **cnev, t_env **exp);
void			ft_export(char **cmd, t_env **cnev, t_env **exp);
void			cd(const char **path, t_env **cenv ,t_env **exp);
void			ft_lstadd_back(t_env **lst, t_env *neww);
int				ft_strlen_b(const char *str);
void			ft_env(t_env *tmp);
void			ft_print_arr(char **arr);
void			ft_builtin(char **cmd, t_env **cenv, t_env **exp);
void			ft_sort_list(t_env **env);
int				ft_strncmp(char *s1, char *s2);
////////////////////////////////////// EXPAND //////////////////
int				count_expand(char *cmd);
char			*ft_expand(t_env *exp, char *cmd);
char            *ft_itoa(int n);

#endif
