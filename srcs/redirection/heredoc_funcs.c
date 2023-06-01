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

void	sigint_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		//printf ("%s\n", g_sigint_exit);
		rl_replace_line(g_sigint_exit, 0);
		rl_done = 1;
		g_sigint_exit = "";
	}
}

int	read_heredoc(t_shell *sh, char *limiter, int expand_sign)
{
	char	*line;

	line = NULL;
	g_sigint_exit = limiter;
	while (1)
	{
		sh->sig.sa_handler = &sigint_heredoc;
		sigaction(SIGINT, &sh->sig, NULL);
		if (sh->pipe_count)
			line = readline("pipe heredoc> ");
		else
			line = readline("heredoc> ");
		if (!*g_sigint_exit)
		{
			free(line);
			free(limiter);
			return (1);
		}
		if (!line || !ft_strcmp(line, limiter))
			break ;
		if (expand_sign)
			line = expand(sh, line);
		ft_putendl_fd(line, sh->heredoc[1]);
		free(line);
	}
	free(line);
	return (0);
}

int	redir_symbol_check(t_shell *sh, char **line, char *redir, int i)
{
	int	expand_sign;

	printf ("redir: %s\n", redir);
	expand_sign = 1;
	if (ft_strchr(redir, '\"') || ft_strchr(redir, '\''))
		expand_sign = 0;
	clear_quotes_line(redir);
	if ((*line)[i] == '<')
	{
		if (err_msg_w_close(pipe(sh->heredoc) < 0, "PipError", \
		sh->pipe_count, sh) || read_heredoc(sh, redir, expand_sign))
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
