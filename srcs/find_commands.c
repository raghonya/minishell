#include <minishell.h>

void	exec_cmd(char **cmds)
{

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

	clear_quotes(cmds);
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
		exec_cmd(cmds);
	i = -1;
	while (cmds[++i])
		free(cmds[i]);
	free(cmds);
}