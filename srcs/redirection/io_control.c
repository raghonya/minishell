#include <minishell.h>

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
	// printf ("\"%s\"\n", *redir);
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
	//printf ("aranc redir: '%s'\n", *line);
	return (0);
}
