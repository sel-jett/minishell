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

static  void    add_args(t_list_arg *list, char *str, int *i)
{
    int     len;
    char    *s;

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
    add_back_arg(list, c_node_arg(s));
}

 void check_syntax_3(t_node *tmp)
{
    char        *str;
    int         i = 0;

    str = NULL;
    if (!tmp-> value){
        tmp->val_vide = 1;
        return ;
    }
    tmp->list_arg = c_list_arg();
    str = tmp->value;
    while (str[i])
    {
        if (str[i] == '$')
            add_args(tmp->list_arg, &str[++i] ,&i);
        i++;
    }
}

bool    plant_4(t_list *list)
{
    t_node  *tmp;

    list->top->prev = NULL;
    if (!list || !list->top)
        return(printf("syntax error !\n"), 0);
    tmp = list->top;
    while (tmp)
    {
        if (tmp->mode == TOKEN_OR || tmp->mode == TOKEN_AND || tmp->mode == TOKEN_PIPE)
            if (!check_syntax_2(tmp) || !check_syntax_1(tmp))
                return(printf("syntax error !\n"), 0);
        if (tmp->mode == TOKEN_REDIR_APPEND || tmp->mode == TOKEN_REDIR_IN || tmp->mode == TOKEN_REDIR_OUT || tmp->mode == TOKEN_HEREDOC)
            if (!check_syntax_1(tmp))
                return(printf("syntax error !\n"), 0);
        if (tmp->mode == TOKEN_Single_Q || tmp->mode == TOKEN_Double_Q)
            check_syntax_3(tmp);
        tmp = tmp->next;
    }
    return (1);
}