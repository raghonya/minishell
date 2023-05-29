/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:09:26 by raghonya          #+#    #+#             */
/*   Updated: 2023/05/01 13:09:28 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_sigint_exit = 0;

void	handle_signals(int signum)
{
	if (signum == SIGINT)
	{
		g_sigint_exit = !g_sigint_exit;
		printf ("handleSig: %d\n", g_sigint_exit);
		rl_replace_line("", 0);
		rl_done = 1;
	}
}

void	prompt_and_history(char **line, char **prompt)
{
	char	*prev_line;

	if (*prompt)
		free(*prompt);
	prev_line = *line;
	*prompt = strjoin_w_free(getcwd(NULL, 0), "$ ");
	*line = *prompt;
	*prompt = ft_strjoin("\033[0;33m", *prompt);
	free(*line);
	*line = readline(*prompt);
	//if (*line)printf ("%s\n", *line);
	if (!*line)
	{
		rl_clear_history();
		printf ("exit\n");
		free(prev_line);
		exit(0);
	}
	if (**line && ft_strcmp(prev_line, *line) && !ft_isspace(**line))
		add_history(*line);
	free(prev_line);
}

void	double_free(char **info)
{
	int	i;

	i = -1;
	if (!info)
		return ;
	while (info[++i])
		free(info[i]);
	free(info);
}

int	free_and_continue(t_shell *sh)
{
	if (check_line(sh))
	{
		change_exit_stat(2, sh->env);
		double_free(sh->paths);
		double_free(sh->spl_pipe);
		return (1);
	}
	double_free(sh->paths);
	double_free(sh->spl_pipe);
	g_sigint_exit = 0;
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		sh;

	(void)argc;
	(void)argv;
	main_inits(&sh, envp);
	while (777)
	{
		prompt_and_history(&sh.line, &sh.prompt);
		if (g_sigint_exit)
		{
			change_exit_stat (1, sh.env);
			g_sigint_exit = !g_sigint_exit;
		}
		if (!*sh.line || check_quotes(sh.line) \
		|| check_pipes(&sh) || check_redirection(&sh))
		{
			change_exit_stat (2, sh.env);
			continue ;
		}
		sh.line = expand(&sh, sh.line);
		//printf ("expanded line: *%s*\n", sh.line);
		if (free_and_continue(&sh))
			continue ;
	}
}

// <a echo <"b" >c barev"ner"sdzezex bayrner | cat srcs/paths/pa"th's".c  | cat >a