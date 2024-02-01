/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 23:16:55 by sel-jett          #+#    #+#             */
/*   Updated: 2024/02/01 22:10:54 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../includes/minishell.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char			*data;
	struct s_env	*next;
}	t_env;

int		ft_strlen_b(const char *str);
t_env	*env_new(char *data);
t_env	*ft_env_parser(char **env);
t_env	*ft_lstlast(t_env *lst);
void ft_list_remove_if(t_env **begin_list, void *data_ref, int (*cmp)());
char	*ft_strdup(char *s);
void	ft_fpintf(const char *msg);
char	*ft_strjoin(char *s1, char *s2);
void	echo(const char *path, int mode);
void	cd(const char *path, t_env **cenv);
void	ft_lstadd_back(t_env **lst, t_env *new);
int		ft_strlen_b(const char *str);

#endif
