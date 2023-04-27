//#include <minishell.h>
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	check_error(char **s, int j)
{
	if (!s[j])
	{
		while (--j >= 0)
			free(s[j]);
		free(s);
	}
	return (j + 1);
}

static int	word_count(char *s, char c)
{
	int	count;
	int	i;
	int	k;

	count = 0;
	i = 0;
	while (1)
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i--])
			break ;
		while (s[++i] && s[i] != c)
		{
			if (s[i] == '\"' || s[i] == '\'')
			{
				k = i;
				while (s[++i] != s[k])
					;
			}
		}
		count++;
	}
	return (count);
}

static int	letter_count(char **s, char c, int *count)
{
	int	quote;
	
	*count = 0;
	while (**s && **s == c)
		(*s)++;
	if (!**s)
		return (1);
	while (**s && **s != c)
	{
		(*count)++;
		if (**s == '\"' || **s == '\'')
		{
			quote = **s;
			while (*++(*s) != quote)
				(*count)++;
			(*count)++;
		}
		(*s)++;
	}
	return (0);
}

static char	**create_lines(char *s, char c, char **split)
{
	int	count;
	int	i;

	i = 0;
	while (1)
	{
		if (letter_count(&s, c, &count))
			break ;
		split[i] = ft_substr(s - count, 0, count);
		if (!check_error(split, i))
			return (NULL);
		i++;
	}
	split[i] = NULL;
	return (split);
}

char	**split_wout_quotes(char *s, char c)
{
	char	**split;

	split = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!split)
		return (split);
	split = create_lines(s, c, split);
	return (split);
}

// int main()
// {
// 	char **s = split_wout_quotes(" \" g  j   j \" p ' l'p a  ");
// 	while (*s)
// 		printf ("-%s-\n", *s++);

// }
