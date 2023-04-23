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

int	word_count(char *s)
{
	int	count;
	int	i;
	int	k;

	count = 0;
	i = 0;
	while (1)
	{
		while (s[i] && s[i] == ' ')
			i++;
		if (!s[i])
			break ;
		if (s[i] == '\"' || s[i] == '\'')
		{
			k = i;
			while (s[++i] != s[k])
				;
		}
		count++;
		while (s[++i] && s[i] != ' ')
			;
	}
	return (count);
}

int	letter_count(char **s, int *count)
{
	int	quote;
	
	*count = 0;
	while (**s && **s == ' ')
		(*s)++;
	if (!**s)
		return (1);
	while (**s && **s != ' ')
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

char	*create_lines(char *s, char **split)
{
	int	count;
	int	i;

	i = 0;
	while (1)
	{
		if (letter_count(&s, &count))
			break ;
		split[i] = ft_substr(s - count, 0, count);
		if (!check_error(split, i))
			return (NULL);
		i++;
	}
	split[i] = NULL;
	return (split[0]);
}

char	**split_wout_quotes(char *s)
{
	char	**split;

	split = malloc(sizeof(char *) * (word_count(s) + 1));
	if (!split)
		return (split);
	create_lines(s, split);
	return (split);
	
}

int main()
{
	char **s = split_wout_quotes(" \" g  j   j \" p ' l'p a  ");
	while (*s)
		printf ("-%s-\n", *s++);

}

//static void	func(const char *s, int *i, int *letcnt)
//{
//	*letcnt = 0;
//	while (s[*i] == c)
//		(*i)++;
//	while (s[*i] != c && s[*i] != 0)
//	{
//		(*letcnt)++;
//		(*i)++;
//	}
//}

//int	stralloc(char const *s, char **split, int wrdcnt)
//{
//	int	i;
//	int	j;
//	int	letcnt;

//	i = (!(j = -1));
//	while (++j < wrdcnt)
//	{
//		while (s[i])
//		{
//			func (s, &i, &letcnt, c);
//			if (letcnt)
//			{
//				split[j] = malloc (sizeof(char) * (letcnt + 1));
//				if (!check_error(split, j))
//					return (0);
//				break ;
//			}
//		}
//	}
//	return (1);
//}

//static char	**fill(char const *s, char **split, int wrdcnt)
//{
//	int	i;
//	int	j;
//	int	let;

//	i = 0;
//	j = 0;
//	while (j < wrdcnt)
//	{
//		let = 0;
//		while (s[i])
//		{
//			while (s[i] == c)
//				i++;
//			while (s[i] != c && s[i] != 0)
//				split[j][let++] = s[i++];
//			split[j][let] = 0;
//			break ;
//		}
//		j++;
//	}
//	split[j] = NULL;
//	return (split);
//}

//char	**split_wout_quotes(char const *s)
//{
//	int		i;
//	int		wrdcnt;
//	char	**split;

//	i = 0;
//	wrdcnt = 0;
//	while (s[i])
//	{
//		while (s[i] == c)
//			i++;
//		if (s[i] != 0)
//			wrdcnt++;
//		while (s[i] != c && s[i] != 0)
//			i++;
//	}
//	split = malloc (sizeof(char *) * (wrdcnt + 1));
//	if (!split)
//		return (NULL);
//	if (!stralloc(s, split, wrdcnt, c))
//		return (NULL);
//	return (fill(s, split, wrdcnt, c));
//}

// #include <stdio.h>

// int main()
// {
// 	char c = ' ', s[1000] = "asdhua shaji rguhe e $^&* 890HU 7237 E9 79 a";
// 	char **s1 = ft_split(s, c);
// 	int i = 0, wrdcnt = 0;
// 	while (s[i])
// 	{
// 		while (s[i] == c)
// 			i++;
// 		if (s[i] != 0)
// 			wrdcnt++;
// 		while (s[i] != c && s[i] != 0)
// 			i++;
// 	}
// 	printf ("%d\n", wrdcnt);
// 	i = 0;
// 	while (i < wrdcnt + 1)
// 	{
// 		printf ("%s ,", s1[i]);
// 		i++;
// 	}
// }
