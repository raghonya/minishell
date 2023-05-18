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

int	g_handle_sigint = 0;

void	prompt_and_history(char **line, char **prompt)
{
	char	*prev_line;

	if (*prompt)
		free(*prompt);
	prev_line = *line;
	*prompt = strjoin_w_free(getcwd(NULL, 0), "$ ");
	*line = readline(*prompt);
	if (!*line)
	{
		printf ("exit\n");
		free(prev_line);
		//system("leaks minishell");
		exit(0);
	}
	printf ("'%s'\n", *line);
	if (**line && ft_strcmp(prev_line, *line) && !ft_isspace(**line))
		add_history(*line);
	free(prev_line);
}

void	double_free(char **info)
{
	int	i;

	i = -1;
	while (info[++i])
		free(info[i]);
	free(info);
}

int	free_and_continue(t_shell *sh)
{
	if (check_line(sh))
	{
		double_free(sh->spl_pipe);
		return (1);
	}
	double_free(sh->spl_pipe);
	return (0);
}

void	handle_sigint(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		printf ("\n");
		rl_on_new_line();
		if (wait(NULL) == -1)
			rl_redisplay();
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		sh;

	(void)argc;
	(void)argv;
	init_env(&sh, envp);
	sh.line = NULL;
	sh.prompt = NULL;
	sh.exit_stat = 0;
	sh.sig.sa_handler = &handle_sigint;
	sigaction(SIGINT, &sh.sig, NULL);
	//DIR	*dir = opendir(".");
	while (777)
	{
		prompt_and_history(&sh.line, &sh.prompt);
		if (!*sh.line || check_quotes(sh.line) \
		|| check_pipes(&sh) || check_redirection(&sh))
			continue ;
		sh.line = expand(&sh, sh.line);
		// printf ("expanded line: *%s*\n", sh.line);
		if (free_and_continue(&sh))
			continue ;
		// system("leaks minishell");
	}
}

// <a echo <"b" >c barev"ner"sdzezex bayrner 
	//| cat srcs/paths/pa"th's".c  | cat >a