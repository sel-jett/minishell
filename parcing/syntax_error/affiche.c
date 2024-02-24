#include "../../includes/minishell.h"

void affiche(t_list *list)
{
		t_node *tmp = list->top;
		while(tmp)
		{
		printf("[prev : %p]            [me :[%p] | val : [%s] | mode : [%d] | is_expend : [%d] | is_space :[%d]]             [next : %p]\n",tmp->prev, tmp, tmp->value, tmp->mode,tmp->flag_expend, tmp->flag_space,tmp->next);
		if (tmp->value[0] && tmp->mode == 11)
		{
			t_nnode *tmp1 = tmp->list_arg->top;
			while(tmp1)
			{
				printf("\nthis is ---------- >[%s]\n",tmp1->value);
				tmp1 = tmp1->next;
			}
		}
		if (tmp->mode == TOKEN_REDIR_APPEND || tmp->mode == TOKEN_REDIR_IN || tmp->mode == TOKEN_REDIR_OUT || tmp->mode == TOKEN_HEREDOC)
		{
			t_nnode *tmp2;

			tmp2 = tmp->list_redir->top;
			printf("-------------------------------------\n");
			while (tmp2)
			{
				printf("-------->%s\n",tmp2->value);
				tmp2 = tmp2->next;
			}
		}
		tmp = tmp->next;
		}
}

void    print_tree(t_node_arbre    *tree, int c)
{
    int i = 0;
    if (!tree)
        return;
	// printf("mode ---> is : %d\n",tree->mode);
	// t_node *node = tree->list->top;
	// printf("--------------------->\n");
	// while (node)
	// {
	// 	printf("[%s] -> ",node->value);
	// 	node =node->next;
	// }
	// printf("\n");
	// (void)c;
    print_tree(tree->right, c + 5);
    while (i < c)
    {
        printf(" ");
        i++;
    }
    if (tree->mode == 5)
        printf("%c ->\n", '|');
    else if (tree->mode == 7)
        printf("%s ->\n", "||");
    else if (tree->mode == 6)
        printf("%s ->\n", "&&");
    else if (tree->mode == 100)
        printf("%c ->\n", 'C');
    else if (tree->mode == 0)
        printf("%s ->\n", tree->value);
    else if (tree->mode == TOKEN_REDIR_IN)
        printf("%c ->\n", '<');
    else
        	printf("%d ->\n", tree->mode);
    // if (tree->mode == 0)
    // {
    //     t_list *tmp ;
    //     tmp = tree->value->redir_in;
    //     while (tmp)
    //     {
    //         printf("redir_in: %s\n", tmp->token);
    //         tmp = tmp->next;
    //     }
    // }
    print_tree(tree->left, c + 5);
}