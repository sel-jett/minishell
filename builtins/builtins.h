/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 23:16:55 by sel-jett          #+#    #+#             */
/*   Updated: 2024/02/02 09:38:17 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../includes/minishell.h"
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

int		ft_strlen_b(const char *str);
char	*value_key(t_env *tmp, char *key);
char	*pwd_joiner(char *temp_old, char *temp, char *path);
t_env	*env_new(char *data);
int		ft_strncmp_one(char *tmp, char *pwd);
int		ft_strncmp_two(char *tmp, char *pwd);
t_env	*ft_env_parser(char **env);
char	*find_pwd(t_env *cenv);
char	*ft_strtrim(char *cmd);
int		check_first(char *cmd);
char	*find_oldpwd(t_env *cenv);
t_env	*ft_lstlast(t_env *lst);
void	ft_list_remove_if(t_env **begin_list, void *data_ref, int (*cmp)());
char	*ft_strdup(char *s);
void	ft_fpintf(const char *msg);
char	*ft_strjoin(char *s1, char *s2);
void	echo(const char *path, int mode);
void	ft_export(char *cmd, t_env **cnev);
void	cd(const char *path, t_env **cenv);
void	ft_lstadd_back(t_env **lst, t_env *neww);
int		ft_strlen_b(const char *str);

#endif
