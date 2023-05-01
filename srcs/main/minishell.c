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

void	clear_quotes_matrix(char **lines)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (lines[++i])
	{
		j = -1;
		while (lines[i][++j])
		{
			if (lines[i][j] && (lines[i][j] == '\"' || lines[i][j] == '\''))
			{
				k = j - 1;
				j = lines[i][j];
				while (lines[i][++k + 1] != j)
					lines[i][k] = lines[i][k + 1];
				j = k-- - 1;
				while (lines[i][++k + 2])
					lines[i][k] = lines[i][k + 2];
				lines[i][k] = 0;
			}
		}
	}
}

void	prompt_and_history(char **line, char **prompt)
{
	char	*prev_line;

	//prev_line = ft_strdup(*line);
	//if (*line)
	//	free(*line);
	if (*prompt)
		free(*prompt);
	prev_line = *line;
	*prompt = strjoin_w_free(getcwd(NULL, 0), "$ ");
	// printf ("prev cmd: %s\n", prev_line);
	*line = readline(*prompt);
	if (!*line)
	{
		printf ("\n");
		free(prev_line);
		//system("leaks minishell");
		exit(0);
	}
	if (**line && ft_strcmp(prev_line, *line) && !ft_isspace(**line))
		add_history(*line);
	free(prev_line);
}

void	free_info(t_shell *sh)
{
	int	i;

	i = -1;
	while (sh->cmds[++i])
		free(sh->cmds[i]);
	free(sh->cmds);
}

int	free_and_continue(t_shell *sh)
{
	if (check_line(sh) || check_pipes(sh))
	{
		free_info(sh);
		return (1);
	}
	free_info(sh);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		sh;

	(void)argc;
	(void)argv;
	init_env(&sh, envp);
	sh.line = NULL;
	sh.prompt = NULL;
	while (777)
	{
		prompt_and_history(&sh.line, &sh.prompt);
		if (!*sh.line || check_quotes(sh.line))
			continue ;
		sh.line = expand(&sh, sh.line);
		//printf ("ret: %s\n\n", sh.line);
		if (free_and_continue(&sh))
			continue ;
	}
}
