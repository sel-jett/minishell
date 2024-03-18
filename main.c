#include "includes/minishell.h"

bool is_redir(t_node *tmp)
{
	if (tmp->mode == TOKEN_HEREDOC || tmp->mode == TOKEN_REDIR_IN ||
		tmp->mode == TOKEN_REDIR_OUT || tmp->mode == TOKEN_REDIR_APPEND)
		return (1);
	return (0);
}

// void	handler_signel(int signal, siginfo_t *siginfo, void *vd)
// {
// 	(void)vd;
// 	(void)siginfo;
// 	if (signal == SIGINT)
// 	{
// 		printf("\n");
// 		rl_on_new_line();
// 		rl_replace_line("",1);
// 		rl_redisplay();
// 	}
// }

void print_in_dot(t_node_arbre *node, int i, int *count, FILE *fp)
{
	if (node == NULL)
		return;
	int node_id = ++(*count);
	if (node->mode == 5)
		fprintf(fp, "  node%d [label=\"%s \"];\n", node_id, "|");
	else if (node->mode == 1)
		fprintf(fp, "  node%d [label=\"%s \"];\n", node_id, ">");
	else if (node->mode == 6)
		fprintf(fp, "  node%d [label=\"%s \"];\n", node_id, "&&");
	else if (node->mode == 7)
		fprintf(fp, "  node%d [label=\"%s \"];\n", node_id, "||");
	else if (node->mode == TOKEN_PARENTHESE)
	{
		fprintf(fp, "  node%d [label=\"%s \"];\n", node_id, "()");
		print_in_dot(node->arbre->racine, node_id, count, fp);
		// print_tree(node->arbre->racine);
	}
	else if (node->mode == TOKEN_REDIR_APPEND)
		fprintf(fp, "  node%d [label=\"%s \"];\n", node_id, ">>");
	else if (node->mode == TOKEN_REDIR_OUT)
		fprintf(fp, "  node%d [label=\"%s %s\"];\n", node_id, ">", node->list_redir->tail->value);
	else if (node->mode == TOKEN_REDIR_IN)
		fprintf(fp, "  node%d [label=\"%s %s\"];\n", node_id, "<", node->value);
	else if (node->mode == TOKEN_EXPR)
	{
		fprintf(fp, "  node%d [label=\"%s \"];\n", node_id, (char *)node->value);
		// while (node->list->top)
		// {
		// 	fprintf(fp, "  node%d [label=\"%s \"];\n", *count, node->list->top->value);
		// 	node->list->top = node->top->next;
		// }
		// node->list->top->value;
	}
	if (i != -1)
	{
		fprintf(fp, "  node%d -> node%d;\n", i, node_id);
	}
	print_in_dot(node->left, node_id, count, fp);
	print_in_dot(node->right, node_id, count, fp);
}

void print_tree(t_node_arbre *root)
{
	FILE *fp;
	int count;

	count = 0;
	fp = stdout;
	fprintf(fp, "digraph {\n");
	print_in_dot(root, -1, &count, fp);
	fprintf(fp, "}\n");
	// fclose(fp);
}

int main(int ac, char **av, char **envp)
{
	t_list *list;
	int i;
	int index;
	t_arbre *arbre;
	t_list *nlist;
	t_env *env;
	t_env *exp;

	list = NULL;
	// struct sigaction	sa;
	// sa.sa_flags = SA_SIGINFO;
	// sa.sa_sigaction = handler_signel;
	// sigaction(SIGINT,&sa,NULL);
	// rl_catch_signals = 0;
	env = ft_env_parser(envp);
	exp = ft_env_parser(envp);
	ft_lstadd_back(&exp, env_new("OLDPWD", exp));
	ft_sort_list(&exp);
	(void)ac;
	(void)envp;
	(void)av;
	while (1)
	{
		(1) && (index = 0, i = 0, list = c_list(), list->str = 0);
		if (!list)
			(1) && (printf("ERROR CREAT LISTE\n") && (index = 1));
		if (!index)
		{
			list->str = readline("minishell > ");
			if (!list->str)
				exit(write(1, "exit\n", 5));
			if (is_empty(list->str))
				index = 1;
			if (!index)
			{
				add_history(list->str); // what's this
				while (list->str[i])
				{
					if (!plants(list, &i))
					{
						index = 1;
						break;
					}
				}
				if (!index)
					if (!plant_4(list))
						index = 1;
				if (!index)
				{
					nlist = c_list();
					if (!nlist)
						index = 1;
					if (!plant_5(list->top, nlist))
						index = 1;
				}
				if (!index)
				{
					arbre = c_arbre();
					if (!arbre)
						index = 1;
				}
				if (!index)
				{
					if (!plant_6(nlist->top, &arbre->racine))
						(1 == 1) && (printf("ERROR7\n"), index = 1);
				}
				if (!index)
				{
					
					// while (arbre->racine->right->list->top)
					// {
					// 	// dprintf(2, "[%s]\n", arbre->racine->right->list->top->value);
					// 	dprintf(2, "[%s][%d]\n", arbre->racine->right->list->top->value, arbre->racine->right->list->top->flag_space);
					// 	arbre->racine->right->list->top = arbre->racine->right->list->top->next;

					// }
					// while (arbre->racine->list_redir->top)
					// {
					// 	// dprintf(2, "[%s]\n", arbre->racine->list_redir->top->value);
					// 	dprintf(2, "[%s][%d][%d]\n", arbre->racine->list_redir->top->value, arbre->racine->list_redir->top->avant_, \
					// 	arbre->racine->list_redir->top->flag_space);
					// 	arbre->racine->list_redir->top = arbre->racine->list_redir->top->next;

					// }
					// printf("[%s][%s][%s]\n",arbre->racine->list_redir->top->value,
					// arbre->racine->list_redir->top->next->value,
					// arbre->racine->list_redir->top->next->next->value);
					// exit(0);
					// env = ft_env_parser(envp);
					// env = ft_env_parser(envp);
					// ft_print_arr(envp);
					// ft_env(env);
					// printf("[%d]\n",arbre->racine->mode);
					// print_tree(arbre->racine);
					// while (arbre->racine->top)
					// {
					// puts(arbre->racine->right->list->top->next->value);
					// 	arbre->racine->top = arbre->racine->list->top->next;
					// }
					// puts(arbre->racine->list->top->value);
					printf("[%d]",arbre->racine->list_redir->top->flag_expend);
					// execute(arbre->racine, env, exp);
					// my_malloc(0, 0);
				}
			}
		}
	}
	return (0);
}