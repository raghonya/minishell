/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:27:58 by raghonya          #+#    #+#             */
/*   Updated: 2023/05/30 16:27:59 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//void	remove_single_quote(char *line)
//{
//	int	i;

//	i = 0;
//	printf ("demic innnnnnn +%s+\n", line);
//	while (line[i])
//	{
//		if (line[i] && line[i + 1] && line[i] == '<' && line[i + 1] == '<')
//		{
//			i += 2;
//			while (line[i] && ft_isspace(line[i]))
//				i++;
			
//			//while (line[i] && !ft_isspace(line[i]) 
//			//&& line[i] != '<' && line[i] != '>')
//			//	ignore_quotes(line, &i);
//			//end_ind = i;
//			//line = new_string(line, start_ind, end_ind);
//		}
//		i++;
//	}

//	//line[ft_strlen(line) - 1] = 0;
//	//while (line[i] != '\'')
//	//	i++;
//	//while (line[i])
//	//{
//	//	line[i] = line[i + 1];
//	//	i++;
//	//}
//	printf ("innnnnnn +%s+\n", line);
//}

int	find_filename(char *line, char **redir, int *index)
{
	int		aft_spc;
	char	*tmp;

	while (ft_isspace(line[++(*index)]))
		;
	aft_spc = *index;
	while (line[*index] && !ft_isspace(line[*index]) \
	&& line[*index] != '<' && line[*index] != '>')
		ignore_quotes(line, index);
	tmp = ft_substr(line, aft_spc, *index - aft_spc);
	err_msg_w_exit (!tmp, 1);
	*redir = ft_strtrim(tmp, " \t\n\r\v\f");
	err_msg_w_exit (!*redir, 1);
	free(tmp);
	printf ("redir in find: %s\n", *redir);
	if (err_msg(!**redir, "syntax error near unexpected token `newline'"))
	{
		free(*redir);
		return (1);
	}
	return (0);
}

char	*clear_redirection(char *line, int start, int end)
{
	char	*ret;
	int		i;

	i = -1;
	ret = malloc(sizeof(char) * (ft_strlen(line) - (end - start + 1) + 1));
	err_msg_w_exit (!ret, EXIT_FAILURE);
	while (++i != start)
		ret[i] = line[i];
	i = end;
	while (line[++i])
		ret[start++] = line[i];
	free(line);
	ret[start] = 0;
	return (ret);
}

int	redirect_io(t_shell *sh, char **line, int i)
{
	int		to_clear;
	char	*redir;

	to_clear = -1;
	if (find_filename(*line + i + 1, &redir, &to_clear))
		return (1);
	clear_quotes_line(redir);
	if ((*line)[i] == '<')
	{
		sh->fdin = open(redir, O_RDONLY);
		free(redir);
		if (err_msg (sh->fdin == -1, "No such file or directory"))
			return (1);
	}
	else
	{
		sh->fdout = open(redir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		free(redir);
		if (err_msg (sh->fdout == -1, "No such file or directory"))
			return (1);
	}
	*line = clear_redirection(*line, i, to_clear + i);
	return (0);
}
