/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:28:03 by raghonya          #+#    #+#             */
/*   Updated: 2023/05/30 16:28:04 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	read_heredoc(t_shell *sh, char *limiter)
{
	char	*line;

	line = NULL;
	while (1)
	{
		if (sh->pipe_count)
			line = readline("pipe heredoc> ");
		else
			line = readline("heredoc> ");
		if (!line || !ft_strcmp(line, limiter))
			break ;
		line = expand(sh, line);
		ft_putendl_fd(line, sh->heredoc[1]);
		free(line);
	}
	free(line);
	return (0);
}

int	redir_symbol_check(t_shell *sh, char **line, char *redir, int i)
{
	if ((*line)[i] == '<')
	{
		if (err_msg_w_close(pipe(sh->heredoc) < 0, "PipError", \
		sh->pipe_count, sh) || read_heredoc(sh, redir))
			return (1);
		sh->fdin = sh->heredoc[0];
		close(sh->heredoc[1]);
		sh->here_closer = 1;
		free(redir);
	}
	else
	{
		sh->fdout = open(redir, O_WRONLY | O_CREAT | O_APPEND, 0644);
		free(redir);
		if (err_msg (sh->fdout == -1, "No such file or directory"))
			return (1);
	}
	return (0);
}

int	heredoc_or_append(t_shell *sh, char **line, int i)
{
	int		to_clear;
	char	*redir;

	to_clear = -1;
	if (find_filename(*line + i + 2, &redir, &to_clear) \
		|| redir_symbol_check(sh, line, redir, i))
		return (1);
	*line = clear_redirection(*line, i, to_clear + i + 1);
	//printf ("aranc redir heredoc: /*%s*/\n", *line);
	return (0);
}
