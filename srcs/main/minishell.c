/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:09:26 by raghonya          #+#    #+#             */
/*   Updated: 2023/05/30 16:44:54 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*g_sigint_exit = "";

void	handle_signals(int signum)
{
	if (signum == SIGINT)
	{
		g_sigint_exit = "1";
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
	printf ("\033[0;33m");
	*line = readline(*prompt);
	printf ("\033[0;97m");
	if (!*line)
	{
		rl_clear_history();
		free(prev_line);
		printf ("exit\n");
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

void	free_and_continue(t_shell *sh)
{
	if (check_line(sh))
	{
		change_exit_stat(2, sh->env);
		if (*g_sigint_exit == '\v')
			change_exit_stat(1, sh->env);
		double_free(sh->paths);
		double_free(sh->spl_pipe);
		g_sigint_exit = "";
		return ;
	}
	change_exit_stat(sh->exit_stat, sh->env);
	double_free(sh->paths);
	double_free(sh->spl_pipe);
	g_sigint_exit = "";
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		sh;

	(void)argc;
	(void)argv;
	main_inits(&sh, envp);
	while (777)
	{
		sig_catcher(&sh);
		prompt_and_history(&sh.line, &sh.prompt);
		if (*g_sigint_exit == '1')
		{
			change_exit_stat (1, sh.env);
			g_sigint_exit = "";
		}
		if (!*sh.line)
			continue ;
		if (check_quotes(sh.line) \
		|| check_pipes(&sh) || check_redirection(&sh))
		{
			change_exit_stat (2, sh.env);
			continue ;
		}
		sh.line = heredoc_change(sh.line);
		sh.line = expand(&sh, sh.line);
		printf ("aft exp: %s\n", sh.line);
		free_and_continue(&sh);
		//system("leaks minishell");
	}
}
