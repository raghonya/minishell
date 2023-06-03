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
	if (!*line)
	{
		rl_clear_history();
		free(prev_line);
		printf ("exit\033[0;97m\n");
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
	g_sigint_exit = "";
	return (0);
}

char	*new_string(char *line, int start, int end)
{
	char	*new;
	int		j;
	int		k;

	new = malloc(sizeof(char) * (ft_strlen(line) + 3));
	err_msg_w_exit(!new, 1);
	j = 0;
	k = 0;
	while (j < start)
		new[k++] = line[j++];
	new[k++] = '\'';
	while (j < end)
		new[k++] = line[j++];
	new[k++] = '\'';
	while (line[j])
		new[k++] = line[j++];
	new[k] = 0;
	free(line);
	return (new);
}

char	*heredoc_change(char *line)
{
	int		start_ind;
	int		end_ind;
	int		i;
	int		k;

	i = 0;
	while (line[i])
	{
		if (line[i] && line[i + 1] && line[i] == '<' && line[i + 1] == '<')
		{
			i += 2;
			while (line[i] && ft_isspace(line[i]))
				i++;
			start_ind = i;
			while (line[i] && !ft_isspace(line[i]))
			{
				if (line[i] == '\"' || line[i] == '\'')
				{
					k = i;
					while (line[++i] != line[k])
						;
				}
				i++;
			}
			end_ind = i;
			line = new_string(line, start_ind, end_ind);
		}
		i++;
	}
	return (line);
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
		// sig_catcher(&sh);
		if (*g_sigint_exit)
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
	}
}
