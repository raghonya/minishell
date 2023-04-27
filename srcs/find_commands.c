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

int	check_line(t_shell sh)
{
	char	**cmds;
	int		i;
	int		j;

	i = -1;
	j = -1;
	cmds = split_wout_quotes(sh.line, ' ');
	err_msg_w_exit(!cmds, 1);
	printf ("\nsplited\n--------------\n");
	while (cmds[++i])
		printf ("%s\n", (cmds[i]));
	printf ("--------------\n");

	clear_quotes_matrix(cmds);
	i  = -1;
	printf ("\nsplited wout quotes\n--------------\n");
	while (cmds[++i])
		printf ("%s\n", (cmds[i]));
	printf ("--------------\n");
	i  = -1;
	if (!ft_strcmp(*cmds, "echo"))
		return (builtin_echo(cmds));
	if (!ft_strcmp(*cmds, "cd"))
		return (builtin_cd(cmds));
	else if (!ft_strcmp(*cmds, "pwd"))
		return (builtin_pwd());
	else if (!ft_strcmp(*cmds, "export"))
		return (builtin_export(cmds, &sh));
	else if (!ft_strcmp(*cmds, "unset"))
		return (builtin_unset(cmds, &sh.env));
	else if (!ft_strcmp(*cmds, "env"))
		return (builtin_env(sh.env));
	else if (!ft_strcmp(*cmds, "exit"))
		return (builtin_exit());
	else
		return (0);
	// i = -1;
	// while (cmds[++i])
	// 	free(cmds[i]);
	// free(cmds);
}