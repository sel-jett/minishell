/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 23:16:55 by sel-jett          #+#    #+#             */
/*   Updated: 2024/02/01 10:01:06 by sel-jett         ###   ########.fr       */
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
	char	*pwd;
	char	*oldpwd;
}	t_env;

int		ft_strlen_b(const char *str);
char	*ft_strdup(char *s);
void	ft_fpintf(const char *msg);
char	*ft_strjoin(char *s1, char *s2);
void	echo(const char *path, int mode);
void	cd(const char *path, t_env *cenv);
int		ft_strlen_b(const char *str);

#endif
