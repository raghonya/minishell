#include <minishell.h>

void	exec_cmd(int pipe_count, char *line)
{
	char	**cmds;
	int		*pipes;
	int		i;

	
	i = -1;
	//printf ("splited\n--------------\n");
	//while (cmds[++i])
	//	printf ("%s\n", (cmds[i]));
	//printf ("--------------\n");
	//clear_quotes_line(line);
	//printf ("string: %s\n", line);
	pipes = malloc(sizeof(int) * pipe_count * 2);
	err_msg_w_exit(!pipes, 1);
	i = -1;
	while (++i < pipe_count)
		err_msg_w_exit(pipe(pipes + (i * 2)) == -1, 1);
	//cmds = ft_split();
	i = -1;
	while (++i < pipe_count + 1)
		;



	i = -1;
	while (++i < pipe_count * 2)
		close(pipes[i]);
	free(pipes);
}

void	check_line(t_shell sh)
{
	char	**cmds;
	int		i;
	int		j;

	i = -1;
	j = -1;
	cmds = split_wout_quotes(sh.line);
	err_msg_w_exit(!cmds, 1);
	//printf ("splited\n--------------\n");
	//while (cmds[++i])
	//	printf ("%s\n", (cmds[i]));
	//printf ("--------------\n");

	clear_quotes_matrix(cmds);
	i  = -1;
	//printf ("after cleaning quotes\n--------------\n");
	//while (cmds[++i])
	//	printf ("%s\n", (cmds[i]));
	//printf ("--------------\n");

	//check_pipes(&sh);
	if (!ft_strcmp(*cmds, "echo"))
		builtin_echo(cmds);
	if (!ft_strcmp(*cmds, "cd"))
		builtin_cd();
	else if (!ft_strcmp(*cmds, "pwd"))
		builtin_pwd();
	else if (!ft_strcmp(*cmds, "export"))
		builtin_export(&sh);
	else if (!ft_strcmp(*cmds, "unset"))
		builtin_unset(&sh);
	else if (!ft_strcmp(*cmds, "env"))
		builtin_env(sh.env);
	else if (!ft_strcmp(*cmds, "exit"))
		;
	else
		exec_cmd(sh.pipe_count, sh.line);
	i = -1;
	while (cmds[++i])
		free(cmds[i]);
	free(cmds);
}