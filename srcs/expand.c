/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:12:02 by raghonya          #+#    #+#             */
/*   Updated: 2023/04/18 20:12:03 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	find_dollar(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

char	*clear_quotes(char *line)
{
	int	i;
	int	j;

	i = -1;

	while (line[++i])
	{
		if (line[i] && (line[i] == '\"' || line[i] == '\''))
		{
			j = i;
			while (line[++i] != line[j])
				;
			if (line[i + 1] && line[i + 1] != ' ')
			{
				j--;
				while (line[++j + 1])
					line[j] = line[j + 1];
				line[j] = 0;
				printf ("%s\n", line);
				printf ("%d, %d\n", i, j);
				j = --i - 1;
				while (line[++j + 1])
					line[j] = line[j + 1];
				line[j] = 0;
			}
		}
	}
}
//	i = -1;
//	while (line[++i])
//	{
//		if (line[i] == '\"' || line[i] == '\'')
//		{
//			j = i-- - 1;
//			while (line[++j + 1])
//				line[j] = line[j + 1];
//			line[j] = 0;
//		}
//	}
//	return (line);

void	create_line(char **line, char **env, t_strs *str)
{
	int	dollar_ind;
	int	length;

	dollar_ind = find_dollar(*line);
	if (dollar_ind == -1)
	{
		str->ret = ft_strdup(*line);
		err_msg_w_exit (!str->ret, 1);
		return ;
	}
	str->ret = NULL;
	while (dollar_ind != -1)
	{
		length = 0;
		str->until_dlr = ft_substr(*line, 0, dollar_ind);
		str->tmp = varname(*line + dollar_ind + 1, &length);
		err_msg_w_exit (!str->tmp || !str->until_dlr, 1);
		str->ret = strjoin_w_free(str->ret, str->until_dlr);
		err_msg_w_exit (!str->ret, 1);
		if (!*str->tmp)
			*line += dollar_ind + length + 1;
		else
			*line += dollar_ind + ft_strlen(str->tmp) + 1;
		str->ret = strjoin_w_free(str->ret, check_env(str->tmp, env, length));
		err_msg_w_exit (!str->ret, 1);
		free(str->until_dlr);
		free(str->tmp);
		dollar_ind = find_dollar(*line);
	}
	str->ret = strjoin_w_free(str->ret, *line);
	err_msg_w_exit (!str->ret, 1);
}

char	*expand(char *line, char **env)
{
	char	*ret_str;
	char	*until_quote;
	t_strs	str;
	int		i;

	i = -1;
	if (find_dollar(line) == -1)
		return (line);
	int	j = -1;
	ret_str = NULL;
	while (line[++i])
	{
		while (line[++j] && line[j] != '\"' && line[j] != '\'')
			;
		until_quote = ft_substr(line, i, j - i);
		str.to_free = until_quote;
		i = j;
		create_line(&until_quote, env, &str);
		ret_str = strjoin_w_free(ret_str, str.ret);
		free(str.to_free);
		free(str.ret);
		if (!line[j])
			break ;
		while (line[++j] != line[i])
			;
		until_quote = ft_substr(line, i, j - i + 1);
		str.to_free = until_quote;
		if (line[i] == '\"')
		{
			
			create_line(&until_quote, env, &str);
			ret_str = strjoin_w_free(ret_str, str.ret);
			free(str.ret);
		}
		else
			ret_str = strjoin_w_free(ret_str, until_quote);
		free(str.to_free);
		i = j;
	}
	free(line);
	return (ret_str);
}

//char	*expand(char *line, char **env)
//{
//	char	*ret_str;
//	char	*until_quote;
//	t_strs	str;
//	int		i;

//	i = -1;
//	if (find_dollar(line) == -1)
//	{
//		return (clear_quotes(line));
//	}
//	int	j = -1;
//	ret_str = NULL;
//	while (line[++i])
//	{
//		while (line[++j] && line[j] != '\"' && line[j] != '\'')
//			;
//		until_quote = ft_substr(line, i, j - i);
//		str.to_free = until_quote;
//		i = j;
//		create_line(&until_quote, env, &str);
//		ret_str = strjoin_w_free(ret_str, str.ret);
//		free(str.to_free);
//		free(str.ret);
//		if (!line[j])
//			break ;
//		while (line[++j] != line[i])
//			;
//		until_quote = ft_substr(line, i + 1, j - i - 1);
//		str.to_free = until_quote;
//		if (line[i] == '\"')
//		{
			
//			create_line(&until_quote, env, &str);
//			ret_str = strjoin_w_free(ret_str, str.ret);
//			free(str.ret);
//		}
//		else
//			ret_str = strjoin_w_free(ret_str, until_quote);
//		free(str.to_free);
//		i = j;
//	}
//	free(line);
//	//printf ("ret: *%s*\n", ret_str);
//	return (ret_str);
//}

//barev aya ay /usr/local/bin:/usr/bin:/bin:/usr/games janhehe $HOME ara: echo
//barev aya ay /usr/local/bin:/usr/bin:/bin:/usr/games janhehe $HOME ara: im msh


//barev $]BAREV kam /usr/local/bin:/usr/bin:/bin:/usr/games chnayac $HOME el kareli a $-BAREV i het: echo
//barev $]BAREV kam /usr/local/bin:/usr/bin:/bin:/usr/games chnayac $HOME el kareli a $-BAREV i het: my msh