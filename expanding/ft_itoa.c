#include "../includes/minishell.h"

static void    ft_verf(int *n, long int *m)
{
    if (*m < 0)
    {
        *n = 1;
        *m = (*m) * (-1);
    }
}

static int    ft_size(long int n)
{
    long int    count;

    count = 0;
    if (n < 0)
    {
        count++;
        n = -n;
    }
    while (n >= 10)
    {
        n = n / 10;
        count++;
    }
    return (count + 1);
}

char    *ft_itoa(int n)
{
    int            size;
    long int    m;
    char        *tab;

    m = n;
    n = 0;
    size = ft_size(m);
    tab = malloc(size + 1);
    if (!tab)
        return (0);
    tab[size] = '\0';
    size--;
    ft_verf(&n, &m);
    while (size >= 0)
    {
        tab[size] = m % 10 + 48;
        m = m / 10;
        size--;
    }
    if (n == 1)
        tab[0] = '-';
    return (tab);
}