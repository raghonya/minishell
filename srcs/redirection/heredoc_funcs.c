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
		rl_replace_line(g_sigint_exit, 0);
		rl_done = 1;
		g_sigint_exit = "\v";
	}
}

int	exit_heredoc(t_shell *sh, char *line, char *limiter, int expand)
{
	if (!line || !ft_strcmp(line, limiter))
	{
		if (!line)
			printf ("minishell: warning: here-document %s`%s')\n", \
			"delimited by end-of-file (wanted ", limiter);
		return (1);
	}
	if (expand)
		line = expand_heredoc(sh, line);
	ft_putendl_fd(line, sh->heredoc[1]);
	free(line);
	return (0);
}

int	read_heredoc(t_shell *sh, char *limiter, int expand_sign)
{
	char	*line;

	g_sigint_exit = limiter;
	while (1)
	{
		sh->sig.sa_handler = &sigint_heredoc;
		sigaction(SIGINT, &sh->sig, NULL);
		if (sh->pipe_count)
			line = readline("\033[0;36mpipe heredoc> ");
		else
			line = readline("\033[0;36mheredoc> ");
		if (*g_sigint_exit == '\v')
		{
			sh->exit_stat = 1;
			free(line);
			free(limiter);
			close(sh->heredoc[0]);
			close(sh->heredoc[1]);
			return (1);
		}
		if (exit_heredoc(sh, line, limiter, expand_sign))
			break ;
	}
	free(line);
	return (0);
}

int	redir_symbol_check(t_shell *sh, char **line, char *redir, int i)
{
	int	expand_sign;

	expand_sign = 1;
	if (ft_strchr(redir, '\"') || ft_strchr(redir, '\'') \
		|| ft_strchr(redir, '`'))
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
	return (0);
}
