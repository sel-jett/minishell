#include "../includes/minishell.h"

void	ft_execute_redir(t_node_arbre *tree, t_env **env, t_env **exp)
{
	int				i;
	int				j;
	char			**cmmd;
	char			**path;
	char			**envp;
	struct s_nnode	*tmp;

	i = 0;
	j = -1;
	tmp = tree->list_redir->top;
	while (tree->list_redir->top)
	{
		if (tree->list_redir->top->avant_ == 1)
			i++;
		else
			break ;
		tree->list_redir->top = tree->list_redir->top->next;
	}
	cmmd = my_malloc(sizeof(char *) * (i + 1), 1);
	tree->list_redir->top = tmp;
	while (++j < i)
	{
		cmmd[j] = ft_strdup(tree->list_redir->top->value);
		tree->list_redir->top = tree->list_redir->top->next;
	
	}
	cmmd[j] = NULL;
	envp = env_to_arr(*env);
	path = ft_split(get_path(*env), ':');
	i = 0;
	while (cmmd[i])
	{
		cmmd[i] = ft_expand(cmmd[i]);
		i++;
	}
	if (is_builtin(cmmd[0]))
	{
		ft_builtin(cmmd, env, exp);
		return ;
	}
	ft_execute_child(envp, cmmd, path);
}


void	ft_execute_redir_out(t_node_arbre *tree, t_env	*env, t_env *exp)
{
	int		fd;
	int		status;
	pid_t	pid;

	fd = open(tree->list_redir->tail->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open error");
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		return ;
	}
	if (pid == 0)
	{
		dup2(fd, 1);
		close(fd);
		ft_execute_redir(tree, &env, &exp);
		exit(0);
	}
	waitpid(pid, &status, 0);
	ft_status(status, 1);
}
