/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:49:09 by amel-has          #+#    #+#             */
/*   Updated: 2024/02/27 22:01:39 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef	struct s_nnode
{
	char			*value;
	struct s_nnode	*next;
}t_nnode;

typedef struct s_nlist
{
	struct s_nnode	*top;
	struct s_nnode	*tail;
	int				len;
}t_nlist;

typedef struct s_data
{
	void			*data;
	struct s_data	*next;
}	t_data;

typedef struct s_list t_list;

typedef struct s_node
{
	char			*value;
	struct s_node	*next;
	struct s_node	*prev;
	int				mode;
	int				val_vide;
	t_nlist			*list_arg;
	t_nlist			*list_redir;
	t_list 			*list;
	int				flag_expend;
	int				flag_space;
}	t_node;

struct s_list
{
	t_node	*top;
	t_node	*tail;
	int		len;
	char    *str;
};

enum
{
	TOKEN_EXPR,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_SPACE,
	TOKEN_BRKT_OPEN,
	TOKEN_BRKT_CLOSE,
	TOKEN_Double_Q,
	TOKEN_Single_Q,
	TOKEN_DOLLAR,
	TOKEN_PARENTHESE,
};

typedef struct s_node_arbre
{
	int					mode;
	char				*value;
	int					flag_expend;
	int					flag_space;
	t_list				*list;
	t_nlist				*list_arg;
	t_nlist				*list_redir;
	struct s_node_arbre *left;
	struct s_node_arbre *right;
} t_node_arbre;

typedef struct s_arbre
{
	t_node_arbre	*racine;
} t_arbre;
#endif
