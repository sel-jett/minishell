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

static  int check_syntax_1(t_node *tmp)
{
    int index = 0;

    if (tmp && tmp->next)
        if (tmp->next->mode != TOKEN_SPACE)
            index++;
    if (tmp && tmp->next && tmp->next->next)
        if (tmp->next->next->mode != TOKEN_SPACE)
            index++;
    if (index >= 1)
        return (1);
    return (0);
}

static  int    add_args(t_list_arg *list, char *str, int *i)
{
    int     len;
    char    *s;
    t_node_arg *node;

    len = 0;
    while (str[len] && str[len] != ' ')
        len++;
    s = my_malloc(sizeof(char)*(len + 1), 1);
    len = 0;
    while (str[len] && str[len] != ' ')
    {
        s[len] = str[len];
        len++;
    }
    s[len] = '\0';
    *i += len;
    node = c_node_arg(s);
    if (!node)
        return (0);
    add_back_arg(list, node);
    return (1);
}

int check_syntax_3(t_node *tmp)
{
    char        *str;
    int         i;

    (1 == 1) && (str = NULL, i = 0);
    if (!tmp-> value)
    {
        tmp->val_vide = 1;
        return (1);
    }
    tmp->list_arg = c_list_arg();
    if (!tmp->list_arg)
        return (0);
    str = tmp->value;
    while (str[i])
    {
        if (str[i] == '$')
        {
            if (!add_args(tmp->list_arg, &str[++i] ,&i))
                return (0);
        }
        i++;
    }
    return (1);
}

int    plant_4(t_list *list)
{
    t_node  *tmp;

    list->top->prev = NULL;
    if (!list || !list->top)
        return (printf("syntax error 1!\n"), 0);
    tmp = list->top;
    while (tmp)
    {
        if (tmp->mode == TOKEN_OR || tmp->mode == TOKEN_AND || tmp->mode == TOKEN_PIPE)
        {
            if (!check_syntax_2(tmp) || !check_syntax_1(tmp))
                return (printf("syntax error 2!\n"), 0);
        }
        else if (tmp->mode == TOKEN_REDIR_APPEND || tmp->mode == TOKEN_REDIR_IN || tmp->mode == TOKEN_REDIR_OUT || tmp->mode == TOKEN_HEREDOC)
        {
            if (!check_syntax_1(tmp))
                return (printf("syntax error 3!\n"), 0);
        }
        else if (tmp->mode == TOKEN_Single_Q || tmp->mode == TOKEN_Double_Q)
        {
            if (!check_syntax_3(tmp))
                return (printf("syntax error 3!\n"), 0);
        }
        tmp = tmp->next;
    }
    return (1);
}