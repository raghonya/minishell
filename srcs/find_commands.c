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

void	print_cmds(t_list *a)
{
	while (a)
	{
		printf ("%s\n", a->data);
		a = a->next;
	}
}

void	check_cmd(t_shell sh)
{
	t_list	*cmds;
	//char	**cmds;
	char	*cmd;
	int		i;
	int		j;
	int		dquote;
	int		quote;

	i = -1;
	quote = 0;
	dquote = 0;
	j = -1;
	//clear_quotes(sh.line);
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
	//cmds = ft_split(sh.line, ' ');
	//err_msg_w_exit(!cmds, 1);
	i = -1;
	//printf ("splited:\n");
	//while (cmds[++i])
	//	printf ("%s\n", (cmds[i]));
	//printf ("\n");
	//i = -1;
	//while (cmds[++i])
	//{
	//	int j = -1;
	//	while (cmds[i][++j])
	//	{
	//		if (cmds[i][j] == '\"')
	//			dquote++;
	//		else if (cmds[i][j] == '\'')
	//			quote++;
	//	}
	//}
	while (ft_isspace(*sh.line))
		sh.line++;
	cmd = until_symb(sh.line, " \t\n\r\v\f\"\'");
	sh.line += ft_strlen(cmd);
	//printf ("%s\n", cmd);
	//if (!ft_strcmp(cmd, "echo"))
	//	builtin_echo(sh.line, cmd);
	if (!ft_strcmp(cmd, "cd"))
		builtin_cd();
	else if (!ft_strcmp(cmd, "pwd"))
		builtin_pwd();
	else if (!ft_strcmp(cmd, "export"))
		builtin_export(&sh);
	else if (!ft_strcmp(cmd, "unset"))
		;
	else if (!ft_strcmp(cmd, "env"))
		builtin_env(sh.env);
	else if (!ft_strcmp(cmd, "exit"))
		;
	else
		exec_cmd(cmd);
	free(cmd);
	//i = -1;
	//while (cmds[++i])
	//	free(cmds[i]);
	//free(cmds);
}