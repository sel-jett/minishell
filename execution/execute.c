#include "../includes/minishell.h"

static void	ft_handler(char *env_var, char **env, char **cmmd)
{
	env_var = ft_strjoin("/", env_var);
	// printf(">>>>>>>>> %s\n", env_var);
	if (!access(env_var, F_OK))
	{
		// printf("%s\n", env_var);
		// printf("\\\\\\\\\\\\\\\\\\\\\\ \n");
		// ft_print_arr(cmmd);
		if (!access(env_var, X_OK))
		{
			if (execve(env_var, cmmd, env) == -1)
				write(2, "error execve\n", 16);
			else
				return ;
		}
		else
		{
			write(2, "error execve\n", 16);
				if (!my_malloc(0, 0))
					return ;
		}
	}
}

char	**env_to_arr(t_env *env)
{
	t_env	*tmp;
	char	**arr;
	int		i;

	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	arr = my_malloc(sizeof(char *) * (i + 1), 1);
	i = 0;
	tmp = env;
	while (tmp)
	{
		// exit(1);
		arr[i] = ft_strjoin(tmp->key, "=");
		arr[i] = ft_strjoin(arr[i], tmp->value);
		i++;
		tmp = tmp->next;
	}
	arr[i] = NULL;
	return (arr);
}

static char	*get_path(t_env *env)
{
	while (env)
	{
		if (!ft_strncmp_one(env->key, "PATH"))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	ft_print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

int	liked_size(t_node_arbre *tree)
{
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = tree->list->top;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);

}

char	**linkedlist_to_arr(t_node_arbre *tree)
{
	char	**arr;
	int		i;
	t_node_arbre *tree_tmp;

	tree_tmp = tree;
	i = liked_size(tree_tmp);
	arr = my_malloc(sizeof(char *) * (i + 1), 1);
	i = 0;
	while (tree->list->top)
	{
		arr[i] = ft_strdup(tree->list->top->value);
		puts(tree->list->top->value);
		// puts("///////////");
		i++;
		tree->list->top = tree->list->top->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	ft_execute_cmd(t_node_arbre *tree, t_env *env)
{
	int				i;
	char			*env_var;
	char			**cmmd;
	char			**path;
	char			**envp;
	t_node_arbre 	*tree_tmp;

	tree_tmp = tree;
	envp = env_to_arr(env);
	path = ft_split(get_path(env), '/');
	cmmd = linkedlist_to_arr(tree_tmp);
	i = 0;
	// cmmd = ft_split(tree->value, ' ');
	// (!cmmd[0]) && (write(2, "Invalid commande\n", 17), my_malloc(tree, 0, 0));
	(1) && (env_var = cmmd[0], i = 0);
	while (path[i])
	{
		if (cmmd[0][0] == '/')
			env_var = ft_strjoin("/", (ft_split(tree->value, ' '))[0]);
		else if (cmmd[0][0] != '.')
		{
			env_var = ft_strjoin("/", (ft_split(tree->value, ' '))[0]);
			env_var = ft_strjoin(path[i], env_var);
		}
		ft_handler(env_var, envp, cmmd);
		i++;
	}
	while (waitpid(-1, NULL, 0) > 0);
	// waitpid(pid, NULL, 0);
	// exit(1);
	// (ft_invalid(cmmd[0])) && (my_malloc(0, 0), 0);
}
