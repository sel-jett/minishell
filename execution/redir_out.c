#include "../includes/minishell.h"

int	ft_count_cmd(t_node_arbre *tree)
{
	int	i;

	i = 0;
	while (tree->list_redir->top)
	{
		if (tree->list_redir->top->avant_ == 1 || \
			(tree->list_redir->top->avant_ == 0 && \
		 		ft_strncmp(tree->list_redir->top->value, ">") && \
				 	ft_strncmp(tree->list_redir->top->value, ">>") && \
				 		ft_strncmp(tree->list_redir->top->value, "<")))
			i++;
		tree->list_redir->top = tree->list_redir->top->next;
	}
	return (i);
}

char	**ft_tree_to_cmd(t_node_arbre *tree)
{
	int				i;
	char			**cmmd;
	struct s_nnode	*tmp;

	tmp = tree->list_redir->top;
	i = ft_count_cmd(tree);
	cmmd = my_malloc(sizeof(char *) * (i + 1), 1);
	i = 0;
	tree->list_redir->top = tmp;
	while (tree->list_redir->top)
	{
		if (tree->list_redir->top->avant_ == 1 || (tree->list_redir->top->avant_ == 0 && \
			ft_strncmp(tree->list_redir->top->value, ">") && \
			ft_strncmp(tree->list_redir->top->value, ">>") && \
			ft_strncmp(tree->list_redir->top->value, "<")))
			{
				cmmd[i] = ft_strdup(tree->list_redir->top->value);
				i++;
			}
		tree->list_redir->top = tree->list_redir->top->next;
	}
	cmmd[i] = NULL;
	return (cmmd);
}

void	ft_execute_redir(t_node_arbre *tree, t_env **env, t_env **exp)
{
	int				i;
	char			**cmmd;
	char			**path;
	char			**envp;

	// exit(0);
	envp = env_to_arr(*env);
	path = ft_split(get_path(*env), ':');
	cmmd = ft_tree_to_cmd(tree);
	i = 0;
	while (cmmd[i])
	{
		cmmd[i] = ft_expand(*exp, cmmd[i]);
		i++;
	}
	if (is_builtin(cmmd[0]))
	{
		ft_builtin(cmmd, env, exp);
		return ;
	}
	ft_execute_child(envp, cmmd, path);
}


int	*get_files(struct s_nnode *list)
{
	int				*fd;
	struct s_nnode	*tmp;
	int				i;

	i = 0;
	tmp = list;
	while (tmp)
	{
		if (tmp->avant_ == 2)
			i++;
		tmp = tmp->next;
	}
	tmp = list;
	fd = my_malloc(sizeof(int) * (i + 1), 1);
	i = 0;
	while (tmp)
	{
		if (tmp->avant_ == 2)
		{
			fd[i] = open(tmp->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd[i] == -1)
			{
				ft_printf("minishell: %s", tmp->value);
				ft_printf(": %s\n", strerror(errno));
				return (0);
			}
			i++;
		}
		tmp = tmp->next;
	}
	fd[i] = -100;
	return (fd);
}

void	ft_close_fd(int *fd)
{
	int	i;

	i = 0;
	while (fd[i] != -100)
	{
		close(fd[i]);
		i++;
	}
}

int	*ft_redir_in_files(struct s_nnode *list)
{
	int				*fd;
	struct s_nnode	*tmp;
	int				i;

	i = 0;
	tmp = list;
	while (tmp)
	{
		if (tmp->avant_ == 3)
			i++;
		tmp = tmp->next;
	}
	tmp = list;
	fd = my_malloc(sizeof(int) * (i + 1), 1);
	i = 0;
	while (tmp)
	{
		if (tmp->avant_ == 3)
		{
			fd[i] = open(tmp->value, O_RDONLY);
			if (fd[i] == -1)
			{
				ft_printf("minishell: ", tmp->value);
				ft_printf(": ", strerror(errno));
				ft_printf("\n", NULL);
				return (NULL);
			}
			i++;
		}
		tmp = tmp->next;
	}
	fd[i] = -100;
	return (fd);	
}

int	*ft_append_files(struct s_nnode *list)
{
	int				*fd;
	struct s_nnode	*tmp;
	int				i;

	i = 0;
	tmp = list;
	while (tmp)
	{
		if (tmp->avant_ == 4)
			i++;
		tmp = tmp->next;
	}
	tmp = list;
	fd = my_malloc(sizeof(int) * (i + 1), 1);
	i = 0;
	while (tmp)
	{
		if (tmp->avant_ == 4)
		{
			fd[i] = open(tmp->value, O_CREAT | O_WRONLY | O_APPEND , 0644);
			if (fd[i] == -1)
			{
				ft_printf("minishell: %s", tmp->value);
				ft_printf(": %s\n", strerror(errno));
				return (0);
			}
			i++;
		}
		tmp = tmp->next;
	}
	fd[i] = -100;
	return (fd);
}

void	files_dupper(int *fd, int *sd, int *ad)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (fd[i] != -100)
		i++;
	while (sd[j] != -100)
		j++;
	while (ad[k] != -100)
		k++;
	if (i > 0)
		dup2(fd[i - 1], 1);
	if (j > 0)
		dup2(sd[j - 1], 0);
	if (k > 0)
		dup2(ad[k - 1], 1);
}

void	ft_execute_redir_out(t_node_arbre *tree, t_env	*env, t_env *exp)
{
	int				*fd;
	int				*sd;
	int				*ad;
	struct s_nnode	*tmp;
	struct s_nnode	*smp;
	struct s_nnode	*amp;
	int				orig_stdout;
	int				orig_stdin;

	orig_stdout = dup(1);
	orig_stdin = dup(0);
	// dprintf(2, "lfassi = %s\n", tree->list_redir->top->value);
	// exit(0);
	tmp = tree->list_redir->top;
	smp = tree->list_redir->top;
	amp = tree->list_redir->top;
	ad = ft_append_files(amp);
	sd = ft_redir_in_files(smp);
	fd = get_files(tmp);
	files_dupper(fd, sd, ad);
	ft_close_fd(fd);
	ft_close_fd(sd);
	ft_close_fd(ad);
	ft_execute_redir(tree, &env, &exp);
	dup2(orig_stdout, 1);
	dup2(orig_stdin, 0);
}
