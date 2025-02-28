#include "../includes/parsing.h"

t_allocs* make_new_node(void    *addr)
{
    t_allocs *new;

    new = (t_allocs*)malloc(sizeof(t_allocs));
    new->next = NULL;
    new->addr = addr;
    return (new);
}

void allocs_addback(t_allocs **allocs, void     *addr)
{
    t_allocs    *tmp;

    if (*allocs == NULL)
    {
        *allocs = make_new_node(addr);
        return;
    }
    tmp = *allocs;
    while(tmp->next)
        tmp = tmp->next;
    tmp->next = make_new_node(addr);
}

void    allocs_clean_up(t_allocs **allocs)
{
    if (*allocs == NULL)
    {
        printf("NULL ALLOCS\n ");
        return ;
    }
    t_allocs    *tmp;
    t_allocs    *holder;
    tmp = *allocs;
    while (tmp)
    {
        holder = tmp->next;
        free (tmp->addr);
        free(tmp);
        tmp = holder;
        printf("allocs cleanup!!\n");
    }
    *allocs = NULL;
}