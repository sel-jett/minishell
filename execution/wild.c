/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:26:25 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/21 21:12:30 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int global_checker(char *str)
{
    int i;

    i = 0;
    if (str)
    {
        while (str[i])
        {
            if (str[i] == '*')
                return (1);
            i++;
        }
    }
    return (0);
}

int ft_strncmp_wild(const char *s1, const char *s2, size_t n)
{
    size_t  i;

    i = 0 ;
    while ((s1[i] || s2[i]) && i < n)
    {
        if (s1[i] != s2[i])
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);
        i++;
    }
    return (0);
}

int ft_strlen_wild_end(char *s)
{
    int i;

    i = 0;
    while (s[i] && s[i] != '*')
        i++;
    // printf("%d\n", i);
    // exit
    return (i);
}

int ft_strlen_wild_first(char *s)
{
    int i;
    int j;

    i = 0;
    while (s[i] && s[i] == '*')
        i++;
    j = 0;
    while (s[i] && s[i] != '*')
        (1) && (i++, j++);
    return (j);
}

int ft_strlen_wild_first_count(char *s)
{
    int i;

    i = 0;
    while (s[i] && s[i] == '*')
        i++;
    return (i);
}

int length_accelerator(char *s, char *str)
{
    int j;
    int i;
    unsigned long len;
    
    j = 0;
    i = 0;
    while (str[i] && str[i] == '*')
        i++;
    len = strlen(str + i);
    while (strlen(s + j) != len)
        j++;
    return (j);
}

int only_wild(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] != '*')
            return (0);
        i++;
    }
    return (1);
}

char    *ft_execute_wild(char *str)
{
    DIR     *dir;
    struct  dirent *dp;
    int     len;
    char *sdk;

    sdk = "";
    dir = opendir(".");
     if (ft_strncmp(str, ".") == 0 || only_wild(str) == 0)
    {
        while ((dp = readdir(dir)) != NULL)
        {
            if ((dp->d_name)[0] != '.')
            {
                sdk = ft_strjoin(sdk, dp->d_name);
                if (!sdk)
                    return (NULL);
                sdk = ft_strjoin(sdk, " ");
                if (!sdk)
                    return (NULL);
            }
        }
        return (sdk);
    }
    if (!global_checker(str))
    {
        return (str);
    }
    len = ft_strlen_wild_end(str);
    if (!dir)
        return (perror("opendir"), NULL);
    if (ft_strlen_wild_end(str))
    {
        while ((dp = readdir(dir)) != NULL)
            if (!ft_strncmp_wild(dp->d_name, str, ft_strlen_wild_end(str)))
            {
                if ((dp->d_name)[0] != '.')
                {
                    sdk = ft_strjoin(sdk, dp->d_name);
                    if (!sdk)
                        return (NULL);
                    sdk = ft_strjoin(sdk, " ");
                    if (!sdk)
                        return (NULL);
                }
            }
        return (sdk);
    }
    else if (ft_strlen_wild_first(str))
    {
        while ((dp = readdir(dir)) != NULL)
        {
            if (!ft_strncmp((dp->d_name + length_accelerator(dp->d_name, str)), str + 1))
            {
                if ((dp->d_name)[0] != '.')
                {
                    sdk = ft_strjoin(sdk, dp->d_name);
                    if (!sdk)
                        return (NULL);
                    sdk = ft_strjoin(sdk, " ");
                    if (!sdk)
                        return (NULL);
                }
            }
        }
            return (sdk);
    }
    else
    {
        while ((dp = readdir(dir)) != NULL)
        {
            sdk = ft_strjoin(dp->d_name, " ");
            if (!sdk)
                return (NULL);
        }
        return (sdk);
    }
    closedir(dir);
    return (NULL);
}