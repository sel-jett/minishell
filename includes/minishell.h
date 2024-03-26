/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:48:58 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/26 01:02:49 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include "structs.h"
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

int				g_x;
bool			is_text2(t_node *tmp);
void			ft_count(t_node *node, int *len, int *index);
void			i_node_make(t_node *node, t_node **i_node);
void			read_parse(int *index, t_list *list, t_env *exp, int *n);
void			ctrld(char *str, int *index);
void			add_redir_parse(t_list *list,
					int *index, int n, t_list **nlist);
void			handel_signel_(struct sigaction sa);
int				open_tty(int *n);
void			handler(int signal);
int				open_herdoc_0(t_node *tmp, t_env *exp, int *n);
void			check_(t_node *tmp, t_nnode *redir_node);
int				add_two( t_list *list, int *i, int mode);
int				oxe5(t_node *tmp);
int				check_exp(t_node *tmp);
int				check_apres_parentheses(t_node *node);
int				check_enter_parentheses(t_node *node);
bool			open_herdoc(t_node *node, char **file, t_env *exp, int *n);
bool			ft_strcmp(char *s1, char *s2);
int				ft_strlen(char *str);
char			**array_dupper(char **str);
int				ope(t_node *node);
int				plant_5(t_node	*tmp, t_list *list);
int				add_args(t_nlist *list, char *str, int *i);
void			affichage(int n);
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
int				check_syntax_1(t_node *tmp, t_env *exp, int *n);
int				check_syntax_2(t_node *tmp);
int				check_syntax_3(t_node *tmp);
int				check_syntax_4(t_node *tmp);
t_node_arbre	*add_commade(t_node	*tmp);
int				add_list_redir(t_node *node);
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
int				plant_4(t_list *list, t_env *exp, int *n);
int				check(int c);
int				is_empty(char *str);
int				add_one(t_list	*list, int *i, int mode);
int				add_list_redir(t_node *tmp);
int				plant_6(t_node *top, t_node_arbre **racine);
///////////////////////// EXECUTION //////////////////////////


void			ft_m_error(char *str);
char			*ft_func(char *str);
int				open_outfile(struct s_nnode *wnt, int *fd, int *j, t_env *env);
int				open_appendfile(struct s_nnode *wnt, int *ad, int *k, t_env *env);
char			*ft_wild_joiner(char **ptr3);
char			*wild_sorting(char *str);
char			*ft_str_joiner(char **env_var,
					char **path, char **cmmd, int *i);
void			igno_sig(void);
void			def_sig(void);
char			*return_only_wild(DIR *dir, struct dirent *dp, char *sdk);
void			flag_to_expand(t_node *smp, char **cmmd, int *check, t_env **exp);
int				execute_cmd_child(int check, char ***cmmd);
void			array_structer_2(char **str);
char			*dup_wild(char **cmmd, t_node *smp, int *check);
char			**checkerr(char *str, int *len);
char			**ft_spliter(char **str, char	**str_r);
char			**array_dupper(char **str);
int				ft_count_cmd(t_node_arbre *tree);
char			**ft_tree_to_cmd(t_node_arbre *tree);
void			ft_execute_redir(t_node_arbre *tree, t_env **env, t_env **exp);
int				*get_files(struct s_nnode *list);
void			ft_close_fd(int *fd);
int				*ft_redir_in_files(struct s_nnode *list);
int				*ft_append_files(struct s_nnode *list);
int				ft_dup2(int fd, int std);
int				files_dupper(int *fd, int *sd, int *ad, struct s_nnode *cnt);
int				open_infile(struct s_nnode *wnt, int *sd, int *i, t_env *env);
char			*ft_handler(char **cmmd, char **path);
void			ft_execute_child(char **envp, char **cmmd, char **path);
int				ft_status(int status, bool mode);
void			execute(t_node_arbre *tree, t_env *e, t_env *exp);
void			ft_execute_cmd(t_node_arbre *tree, t_env **env, t_env **exp);
void			ft_execute_pipe(t_node_arbre *tree, t_env *e, t_env *exp);
void			ft_execute_and(t_node_arbre *tree, t_env *e, t_env *exp);
void			ft_execute_or(t_node_arbre *tree, t_env *e, t_env *exp);
void			ft_execute_subshell(t_node_arbre *tree, t_env *e, t_env *exp);
void			ft_execute_redir_out(t_node_arbre *tree,
					t_env	*env, t_env *exp);
void			count_joyner(char **str, int *len);
void			ft_printf(const char *str, const char *str2);
void			backslach_filler(char **str);
void			ft_execve(char *env_var, char **env, char **cmmd);
char			**env_to_arr(t_env *env);
void			ft_print_arr(char **arr);
char			**arr_filler(t_node	*tmp, char **arr, int i, t_env *exp);
int				liked_size(t_node *tree);
char			**linkedlist_to_arr(t_node *tree, t_env *exp);
char			*get_path(t_env *env);
char			**redirlist_to_arr(t_nlist *list_redir);
int				length(char *s, char *str);
int				only_wild(char *str);
int				is_alpha_4(char c);
char			*ft_execute_wild(char *str);
///////////////////////// BUILTINS //////////////////////////

int				is_alpha(int c);
int				is_num(int c);
int				ft_isdigit(char c);
void			erorr_builtins(char *cmd);
int				ft_atoi(const char *str);
int				check_key(char *key);
void			exit_print(char *str);
int				first_key_checker(char *cmmd);
int				contain_wild(char *str);
int				global_checker(char *str);
int				chekcer(char *data);
char			*cd_init(t_env **cenv, t_env **exp, char *pwd);
int				ft_strncmp_wild(const char *s1, const char *s2, size_t n);
int				ft_strlen_wild_end(char *s);
int				ft_strlen_wild_first(char *s);
int				ft_strlen_wild_first_count(char *s);
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
int				check_first(char *cmd, t_env *exp);
char			*find_oldpwd(t_env *cenv);
t_env			*ft_lstlast(t_env *lst);
void			ft_list_remove_if(t_env **begin_list,
					void *data_ref, int (*cmp)());
char			*ft_strdup(char *s);
void			ft_fpintf(const char *msg);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strjoin2(char *s1, char *s2);
void			echo(const char **path, int mode);
int				ft_cmp(char *s1, char *s2);
void			ft_unset(char **cmd, t_env **cnev, t_env **exp);
void			ft_export(char **cmd, t_env **cnev, t_env **exp);
void			cd(const char **path, t_env **cenv, t_env **exp);
void			ft_lstadd_back(t_env **lst, t_env *neww);
int				ft_strlen_b(const char *str);
void			ft_env(t_env *tmp);
void			ft_print_arr(char **arr);
void			ft_builtin(char **cmd, t_env **cenv, t_env **exp);
void			ft_sort_list(t_env **env);
int				ft_strncmp(char *s1, char *s2);
char			*path_getter(char	*temp, t_env *cenv,
					int i, const char **path);
int				cd_error(const char *path);
void			cd_second(void);
int				cd_old(const char *path);
int				cd_home(const char *path);
void			cd_application(t_env **cenv, t_env **exp,
					char *b, const char **path);
////////////////////////////////////// EXPAND //////////////////

char			*expander(char *new_cmd, char *cmd, t_env *exp);
char			*ft_strjoin_char(char *s1, char s2);
char			*exp_mlc(int *i, int *k, char *cmd);
void			ct_exp(int *i, int *k, char *cmd);
int				count_expand(char *cmd);
char			*ft_expand(t_env *exp, char *cmd);
char			*ft_itoa(int n);
int				is_alpha_3(char c);
char			**joyner(char **str);
#endif
