#include <minishell.h>

void	exec_cmd(char *cmd)
{

}

//void	split_line(t_list *cmds, char *line, int *i)
//{
//	while (line[*i] && )
//	{

//	}
//}

void	check_line(t_shell sh)
{
	char	**cmds;
	int		i;
	int		j;

	i = -1;
	j = -1;
	printf ("%s\n", sh.line);
	cmds = split_wout_quotes(sh.line);
	err_msg_w_exit(!cmds, 1);
	printf ("splited\n--------------\n");
	while (cmds[++i])
		printf ("%s\n", (cmds[i]));
	printf ("--------------\n");

	clear_quotes(cmds);
	i  = -1;
	printf ("after cleaning quotes\n--------------\n");
	while (cmds[++i])
		printf ("%s\n", (cmds[i]));
	printf ("--------------\n");

	if (!ft_strcmp(*cmds, "echo"))
		builtin_echo(cmds);
	if (!ft_strcmp(*cmds, "cd"))
		builtin_cd();
	else if (!ft_strcmp(*cmds, "pwd"))
		builtin_pwd();
	else if (!ft_strcmp(*cmds, "export"))
		builtin_export(&sh);
	else if (!ft_strcmp(*cmds, "unset"))
		;
	else if (!ft_strcmp(*cmds, "env"))
		builtin_env(sh.env);
	else if (!ft_strcmp(*cmds, "exit"))
		;
	else
		exec_cmd(*cmds);
	i = -1;
	while (cmds[++i])
		free(cmds[i]);
	free(cmds);
	//printf ("%s\n", sh.line);
	//while (sh.line[++j])
	//{
	//}
	//cmds = NULL;
	//while (sh.line[++i])
	//{
	//	while (sh.line[++j] && sh.line[j] != '\"' && sh.line[j] != '\'')
	//		;
	//	if (j > i)
	//		ft_lstadd_back(&cmds, ft_lstnew(ft_substr(sh.line, i, j - i)));
	//	i = j;
	//	if (!sh.line[j])
	//		break ;
	//	while (sh.line[++j] != sh.line[i])
	//		;
	//	if (j > i + 1)
	//		ft_lstadd_back(&cmds, ft_lstnew(ft_substr(sh.line, i, j - i + 1)));
	//	i = j;
	//}
	//print_cmds(cmds);
	// i = -1;
	// while (cmds[++i])
	// {
	// 	int j = -1;
	// 	while (cmds[i][++j])
	// 	{
	// 		if (cmds[i][j] == '\"')
	// 			dquote++;
	// 		else if (cmds[i][j] == '\'')
	// 			quote++;
	// 	}
	// }


	// while (ft_isspace(*sh.line))
	// 	sh.line++;
	// cmd = until_symb(sh.line, " \t\n\r\v\f\"\'");
	// sh.line += ft_strlen(cmd);
	//printf ("%s\n", cmd);
	// free(cmd);
}