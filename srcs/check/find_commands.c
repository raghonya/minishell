/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:08:07 by raghonya          #+#    #+#             */
/*   Updated: 2023/05/01 13:08:07 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec_cmd(int pipe_count, char *line)
{
	char	**cmds;
	int		*pipes;
	int		i;

	
	i = -1;
	cmds = split_wout_quotes(line, '|');
	printf ("\nsplited with '|'\n--------------\n");
	while (cmds[++i])
		printf ("%s\n", (cmds[i]));
	printf ("--------------\n");
	// clear_quotes_line(line);
	// printf ("string: %s\n", line);
	pipes = malloc(sizeof(int) * pipe_count * 2);
	err_msg_w_exit(!pipes, 1);
	i = -1;
	while (++i < pipe_count)
		err_msg_w_exit(pipe(pipes + (i * 2)) == -1, 1);
	i = -1;
	while (++i < pipe_count + 1)
		;



	i = -1;
	while (++i < pipe_count * 2)
		close(pipes[i]);
	free(pipes);
}

int	check_line(t_shell *sh)
{
	int		i;
	int		j;

	i = -1;
	j = -1;

	sh->cmds = split_wout_quotes(sh->line, ' ');
	err_msg_w_exit(!sh->cmds, 1);
	if (check_redirections(sh, ft_strdup(sh->line)))
		return (1);
	printf ("\nsplited\n--------------\n");
	while (sh->cmds[++i])
		printf ("%s\n", (sh->cmds[i]));
	printf ("--------------\n");
	i = -1;
	// red = split_wout_quotes(sh->line, '<');
	// err_msg_w_exit(!sh->cmds, 1);
	// printf ("\nsplited w < \n--------------\n");
	// while (red[++i])
	// 	printf ("%s\n", (red[i]));
	// printf ("--------------\n");

	// clear_quotes_matrix(sh->cmds);

	i = -1;
	// printf ("\nsplited wout quotes\n--------------\n");
	// while (sh->cmds[++i])
	// 	printf ("%s\n", (sh->cmds[i]));
	// printf ("--------------\n");
	//i  = -1;
	if (!ft_strcmp(*sh->cmds, "echo"))
		return (builtin_echo(sh->cmds));
	if (!ft_strcmp(*sh->cmds, "cd"))
		return (builtin_cd(sh->cmds, sh->env));
	else if (!ft_strcmp(*sh->cmds, "pwd"))
		return (builtin_pwd());
	else if (!ft_strcmp(*sh->cmds, "export"))
		return (builtin_export(sh->cmds, sh));
	else if (!ft_strcmp(*sh->cmds, "unset"))
		return (builtin_unset(sh->cmds, &sh->env));
	else if (!ft_strcmp(*sh->cmds, "env"))
		return (builtin_env(sh->env));
	else if (!ft_strcmp(*sh->cmds, "exit"))
		return (builtin_exit(sh->cmds));
	else
		return (0);
	// i = -1;
	// while (cmds[++i])
	// 	free(cmds[i]);
	// free(cmds);
}
//	echo >a >b >c  -n >d >e >f  barev >a iuytresdfghj