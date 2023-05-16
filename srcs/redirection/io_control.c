#include <minishell.h>

// check filename, arajin elementy inch kara lini
//  && (line[*index] == '_' || 
// 		line[*index] == '.' || line[*index] == '-' || 
//	(line[*index]) || line[*index] == '\"' || line[*index] == '\'')
// animast check
int	find_filename(char *line, char **redir, int *index)
{
	char	*tmp;
	int		aft_spc;
	int		k;

	while (ft_isspace(line[++(*index)]))
		;
	aft_spc = *index;
	while (line[*index] && !ft_isspace(line[*index]))
	{
		if (line[*index] == '\"' || line[*index] == '\'')
		{
			k = *index;
			while (line[++(*index)] != line[k])
				;
		}
		(*index)++;
	}
	tmp = ft_substr(line, aft_spc, *index - aft_spc);
	err_msg_w_exit (!tmp, 1);
	*redir = ft_strtrim(tmp, " \t\n\r\v\f");
	err_msg_w_exit (!*redir, 1);
	free(tmp);
	clear_quotes_line(*redir);
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

int	read_heredoc(t_shell *sh, char *redir)
{
	char	*limiter;
	char	*line;

	line = NULL;
	limiter = ft_strjoin(redir, "\n");
	printf ("limiter: %s", limiter);
	err_msg_w_exit (!limiter, 1);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line || !ft_strcmp(line, limiter))
			break ;
		line = expand(sh, line);
		write (sh->heredoc[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	free(limiter);
	return (0);
}

int	heredoc_or_append(t_shell *sh, char **line, int i)
{
	int		to_clear;
	char	*redir;

	to_clear = -1;
	find_filename(*line + i + 2, &redir, &to_clear);
	if (err_msg (!*redir, "syntax error near unexpected token"))
		return (1);
	if ((*line)[i] == '<')
	{
		if (err_msg_w_close(pipe(sh->heredoc) < 0, "PipError", \
		sh->pipe_count, sh) || read_heredoc(sh, redir))
			return (1);
		sh->fdin = sh->heredoc[0];
		sh->here_closer = close(sh->heredoc[1]) + 1;
		free(redir);
	}
	else
	{
		sh->fdout = open(redir, O_WRONLY | O_CREAT | O_APPEND, 0644);
		free(redir);
		if (err_msg (sh->fdout == -1, "No such file or directory"))
			return (1);
	}
	*line = clear_redirection(*line, i, to_clear + i + 1);
	printf ("aranc redir heredoc: /*%s*/\n", *line);
	return (0);
}

int	redirect_io(t_shell *sh, char **line, int i)
{
	int		to_clear;
	char	*redir;

	to_clear = -1;
	find_filename(*line + i + 1, &redir, &to_clear);
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
	printf ("aranc redir: '%s'\n", *line);
	return (0);
}
