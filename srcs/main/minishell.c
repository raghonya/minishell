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
#include <termios.h>

int	g_handle_sig = 0;

int	readline_break(void)
{
	return (0);
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
		double_free(sh->paths);
		double_free(sh->spl_pipe);
		return (1);
	}
	double_free(sh->paths);
	double_free(sh->spl_pipe);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		sh;
	//struct termios	term;

	//tcgetattr(STDIN_FILENO, &term);
	////term.c_cc[VINTR] = 'z';
	//term.c_lflag &= ~ECHO;
	//tcsetattr(STDIN_FILENO, TCSANOW, &term);
	//tcgetattr(STDIN_FILENO, &term);
	(void)argc;
	(void)argv;
	rl_event_hook = &readline_break;
	init_env(&sh, envp);
	sh.line = NULL;
	sh.paths = NULL;
	sh.prompt = NULL;
	sh.exit_stat = 0;
	sig_catcher(&sh);
	////DIR	*dir = opendir(".");
	while (777)
	{
		// unset u exit mej sh argumenty hanel
		prompt_and_history(&sh.line, &sh.prompt);
		if (!*sh.line || check_quotes(sh.line) \
		|| check_pipes(&sh) || check_redirection(&sh))
			continue ;
		sh.line = expand(&sh, sh.line);
		//printf ("expanded line: *%s*\n", sh.line);
		if (free_and_continue(&sh))
			continue ;
		// system("leaks minishell");
	}
}

// <a echo <"b" >c barev"ner"sdzezex bayrner | cat srcs/paths/pa"th's".c  | cat >a