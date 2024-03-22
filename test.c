#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

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
	str[i] = 0;
	return (str);
}

void c(char **str,int *len)
{
    int i = 0;
    int j = 0;

    while (str[i])
    {
        j = 0;
        while(str[i][j] !='\\' && str[i][j])
        {
            (*len)++;
            j++;
        }
        if (str[i][j] != '\\')
            (*len)++;
        i++;
    }
}

char **f(char **str)
{
    int i = 0;
    int j = 0;
    int len = 0;
    int k = 0;

    c(str, &len);
    char *str_r = malloc(sizeof(char)*(len+1));
    if (!str_r)
        return (0);
    while (str[i])
    {
        j = 0;
        while(str[i][j] !='\\' && str[i][j])
        {
            str_r[k] = str[i][j];
            k++;
            j++;
        }
        if (str[i][j] !='\\')
            str_r[k++] = ' ';
        i++;
    }
    str_r[k] = '\0';

    char **s_f = ft_split(str_r,' ');
    return (s_f);
}

int main()
{
    // char **str = malloc(sizeof(char *) * 5);
    // if (!str)
    //     return (0);
    // str[0] = "\\";
    // str[1] = "y";
    // str[2] = "x";
    // str[3] = "c";
    // str[4] = 0;
    // char **s = f(str);
    // int i = 0;
    // while (s[i])
    // {
    //     printf("%s\n",s[i]);
    //     i++;
    // }
	int i = 0;
	printf("%d\n", (i == 0));
}
