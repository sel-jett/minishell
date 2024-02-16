#include "../../includes/minishell.h"

static int check_syntax_2(t_node *tmp)
{
    int index = 0;
    if (tmp && tmp->prev)
        if (tmp->prev->mode != TOKEN_SPACE)
            index++;
    if (tmp && tmp->prev && tmp->prev->prev)
        if(tmp->prev->prev->mode != TOKEN_SPACE)
            index++;
    if (index >= 1)
        return (1);
    return (0);
}
static int check_syntax_1(t_node *tmp)
{
    int index = 0;

    if(tmp && tmp->next)
        if (tmp->next->mode != TOKEN_SPACE)
            index++;
    if (tmp && tmp->next && tmp->next->next)
        if (tmp->next->next->mode != TOKEN_SPACE)
            index++;
    if (index >= 1)
        return (1);
    return (0);
}

bool    plant_4(t_list *list)
{
    t_node  *tmp;

    list->top->prev = NULL;
    if (!list || !list->top)
        return (0);
    tmp = list->top;
    while (tmp)
    {
        if (tmp->mode == TOKEN_OR || tmp->mode == TOKEN_AND || tmp->mode == TOKEN_PIPE)
            if (!check_syntax_2(tmp))
                exit(write(1,"syntax error !\n",15));
        if (tmp->mode == TOKEN_REDIR_APPEND || tmp->mode == TOKEN_REDIR_IN || tmp->mode == TOKEN_REDIR_OUT || tmp->mode == TOKEN_HEREDOC)
            if (!check_syntax_1(tmp))
                exit(write(1,"syntax error !\n",15));
        tmp = tmp->next;
    }
    return (1);
}