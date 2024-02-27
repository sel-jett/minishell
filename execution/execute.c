#include "../includes/minishell.h"

// static void	ft_handler(char *env_var, char **env, char **cmmd)
// {
// 	if (!access(env_var, F_OK))
// 	{
// 		if (!access(env_var, X_OK))
// 		{
// 			if (execve(env_var, cmmd, env) == -1)
// 			{
// 				write(2, "error execition\n", 16);
// 				if (!my_malloc(0, 0))
// 					return ;

// 			}
// 		}
// 		else
// 		{
// 			write(2, "error execition\n", 16);
// 				if (!my_malloc(0, 0))
// 					return ;
// 		}
// 	}
// }

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

void	ft_execute_cmd(t_node_arbre *tree, t_env **env)
{
	int		i;
	char	*env_var;
	char	**cmmd;
	char	**path;

	path = ft_split(get_path(*env), '/');
	cmmd = ft_split(tree->value, ' ');
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
		// ft_handler(env_var, env, cmmd);
		i++;
	}
	// (ft_invalid(cmmd[0])) && (my_malloc(0, 0), 0);
}
