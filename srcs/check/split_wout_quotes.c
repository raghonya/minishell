//#include <minishell.h>

//static int	check_error(char **s, int j)
//{
//	if (!s[j])
//	{
//		while (--j >= 0)
//			free(s[j]);
//		free(s);
//		s = NULL;
//	}
//	return (j + 1);
//}

//static int	word_count(char *s, char c)
//{
//	int	count;
//	int	i;
//	int	k;

//	count = 0;
//	i = 0;
//	while (1)
//	{
//		while (s[i] && s[i] == c)
//			i++;
//		if (!s[i--])
//			break ;
//		while (s[++i] && s[i] != c)
//		{
//			if (s[i] == '\"' || s[i] == '\'')
//			{
//				k = i;
//				while (s[++i] != s[k])
//					;
//			}
//		}
//		count++;
//	}
//	return (count);
//}

//static int	letter_count(char **s, char c, int *count)
//{
//	int	quote;

//	*count = 0;
//	while (**s && **s == c)
//		(*s)++;
//	if (!**s)
//		return (1);
//	while (**s && **s != c)
//	{
//		(*count)++;
//		if (**s == '\"' || **s == '\'')
//		{
//			quote = **s;
//			while (*++(*s) != quote)
//				(*count)++;
//			(*count)++;
//		}
//		(*s)++;
//	}
//	return (0);
//}

//static void	create_lines(char *s, char c, char **split)
//{
//	int	count;
//	int	i;

//	i = 0;
//	while (1)
//	{
//		if (letter_count(&s, c, &count))
//			break ;
//		split[i] = ft_substr(s - count, 0, count);
//		if (!check_error(split, i))
//			return ;
//		i++;
//	}
//	split[i] = NULL;
//}

//char	**split_wout_quotes(char *s, char c)
//{
//	char	**split;

//	split = malloc(sizeof(char *) * (word_count(s, c) + 1));
//	if (!split)
//		return (split);
//	create_lines(s, c, split);
//	return (split);
//}

#include <minishell.h>

static int	check_error(char **s, int j)
{
	if (!s[j])
	{
		while (--j >= 0)
			free(s[j]);
		free(s);
		s = NULL;
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
			if (s[i] == '>' || s[i] == '<')
			{
				while (s[++i] && ft_isspace(s[i]))
					;
				//printf ("%c\n", s[i]);
				//if (s[i] == '>' || s[i] == '<')
				//	i++;
				if (!s[i--])
					break ;
				while (s[++i] && s[i] != c && s[i] != '\"' \
					&& s[i] != '\'' && s[i] != '<' && s[i] != '>')
					;
			}
			if (s[i] == '\"' || s[i] == '\'')
			{
				k = i;
				while (s[++i] != s[k])
					;
			}
			if (!s[i] || s[i] == c)
				break ;
		}
		count++;
	}
	printf ("%d\n", count);
	return (count);
}

static int	letter_count(char **s, char c, int *count)
{
	int	quote;

	*count = 0;
	while (**s && **s == c)
		(*s)++;
	if (!*(*s)--)
		return (1);
	while (*++(*s) && **s != c)
	{
		(*count)++;
		if (**s == '>' || **s == '<')
		{
			while (*++(*s) && ft_isspace(**s))
				(*count)++;
			//if (**s == '>' || **s == '<')
			//{
			//	(*s)++;
			//	(*count)++;
			//}
			if (!*(*s)--)
				break ;
			while (*++(*s) && **s != c && **s != '\"' \
				&& **s != '\'' && **s != '>' && **s != '<')
				(*count)++;
			if (**s == '\"' || **s == '\'')
				(*count)++;
		}
		if (**s && **s == '\"' || **s == '\'')
		{
			quote = **s;
			while (*++(*s) != quote)
				(*count)++;
			(*count)++;
		}
		if (!**s || **s == c)
			break ;
	}
	return (0);
}

static void	create_lines(char *s, char c, char **split)
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
			return ;
		i++;
	}
	split[i] = NULL;
}

char	**split_wout_quotes(char *s, char c)
{
	char	**split;

	split = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!split)
		return (split);
	create_lines(s, c, split);
	return (split);
}