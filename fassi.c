#include <stdio.h>
#include<stdlib.h>
#include <string.h>
static int	count_words(char const *str, char c)
{
	int	index;
	int	count;
	int	i;

	count = 0;
	index = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			index = 0;
		else if (index == 0)
		{
			count++;
			index = 1;
		}
		i++;
	}
	return (count);
}

static char	*get_word(const char *s, char c)
{
	char	*word;
	size_t	len;
	size_t	i;

	i = -1;
	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = (char *)malloc(len + 1);
	if (!word)
		return (0);
	while ((++i) < len)
		word[i] = s[i];
	word[len] = '\0';
	return (word);
}

static void	*ft_free(char **arr, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(arr[i++]);
	free(arr);
	return (0);
}

char	**ft_split(const char *s, char c)
{
	char	**str;
	int		i;

	i = 0;
	if (!s)
		return (0);
	str = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!str)
		return (0);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			str[i] = get_word(s, c);
			if (!str[i])
				return (ft_free(str, i));
			while (*s && *s != c)
				s++;
			i++;
		}
	}
	str[i] = NULL;
	return (str);
}

void c(char **str, int *len)
{
    int		i;
    int		j;
    char	**s;

	i = 0;
    while (str[i])
    {
        if (str[i][strlen(str[i]) - 1] == '*')
        {
        	j = 0;
			s =  ft_split(str[i], ' ');
			while (s[j])
			{
			     (*len)++;
			     j++;
			}
        }
        (*len)++;
        i++;
    }
}

char **f(char **str, int i, int j, int k)
{
    int		len;
    char	**s;
    char	**str_r;

    (1) && (len = 0, c(str, &len), 0);
    str_r = malloc(sizeof(char *) * (len + 1));
    if (!str_r)
        return (0);
    while (str[i])
    {
        if (str[i][strlen(str[i]) - 1] == '*')
        {
            j = 0;
            s =  ft_split(str[i], ' ');
            while (s[j])
            {
                 str_r[k] = strdup(s[j]);
				 (1) && (j++, k++);
            }
        }
        else
            str_r[k++] = strdup(str[i]);
        i++;
    }
    return (str_r[k] = NULL, str_r);
}

void change(char **str)
{
	int i = 0;
    while (str[i])
    {
        if (str[i][strlen(str[i]) - 1] == '*')
			str[i][strlen(str[i]) - 1] = '\0';
        i++;
    }
}

int main()
{
	int x = 0;
	int j = 0;
	int  k = 0;
	char **str = malloc(sizeof(char *) * 5);
	str[0] = "amine el hassak";
	str[1] = "aminek l*";
	str[2] = "ana hna*";
	str[3] = "";
	char **s = f(str,x,j,k);
	change(s);
	int i = 0;
	while (s[i])
	{
		printf("[%s]\n",s[i]);
		i++;
	}

}
