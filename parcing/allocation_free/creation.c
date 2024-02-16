#include "../../includes/minishell.h"

t_node    *c_node(char *str, t_node *tail, int mode)
{
    t_node *new_node;

    new_node = my_malloc(sizeof(t_node),1);
    if (!new_node)
        return (0);
    new_node->value = str;
    new_node->next = NULL;
    new_node->prev = tail;
    new_node->mode = mode;
    new_node->val_vide = 0;
    new_node->list_arg = NULL;
    return (new_node);
}

t_list *c_list()
{
    t_list *new_list;

    new_list = my_malloc(sizeof(t_list),1);
    if(!new_list)
        return (0);
    new_list->len = 0;
    new_list->top = NULL;
    return (new_list);
}

void    add_back(t_list *list, t_node *node)
{
    t_node *tmp;

    if (!list)
        return ;
    if (!list->top)
    {
        list->top = node;
        list->tail = node;
        list->len++;
        return;
    }
    tmp = list->top;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;
    list->tail = node;
    list->tail->next = NULL;
    list->len++;
}

void    add_back_arg(t_list_arg *list, t_node_arg *node)
{
    t_node_arg *tmp;

printf("ha na hna\n");
    if (!list)
        return ;
    if (!list->top)
    {
        list->top = node;
        list->tail = node;
        list->len++;
        return;
    }
    tmp = list->top;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;
    list->tail = node;
    list->tail->next = NULL;
    list->len++;
}

t_node_arg *c_node_arg(char *str)
{   
    t_node_arg *new_node_arg;
    
    new_node_arg = my_malloc(sizeof(t_node_arg),1);
    if (!new_node_arg)
        return (0);
    new_node_arg->value = str;
    new_node_arg->next = NULL;
    return (new_node_arg);
}

t_list_arg  *c_list_arg()
{
    t_list_arg *new_arg;

    new_arg = my_malloc(sizeof(t_list_arg), 1);
    if (!new_arg)
        return (0);
    new_arg->top = NULL;
    new_arg->tail = NULL;
    new_arg->len = 0;
    return new_arg;
}