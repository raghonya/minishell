#include <minishell.h>

char	*filename(char *str)
{
	char	*name;
	int		i;

	printf ("str do <>: %s\n", str);
	i = -1;
	while (ft_isspace(str[++i]))
		;
	str += ++i;
	printf ("str after <>: %s\n", str);
	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' \
		|| str[i] == '-' || str[i] == '.'))
		i++;
	name = malloc(sizeof(char) * (i + 1));
	i = 0;
	err_msg_w_exit(!name, 1);
	while (*str && (ft_isalnum(*str) || *str == '_' \
		|| *str == '-' || *str == '.'))
		name[i++] = *str++;
	name[i] = 0;
	printf ("name of the file: %s\n", name);
	return (name);
}

void	check_redirections(t_shell *sh)
{
	char	*name;
	int		i;
	int		j;

	i = -1;
	while (sh->cmds[++i])
	{
		j = -1;
		while (sh->cmds[i][++j])
		{
			if (sh->cmds[i][j] == '<' || sh->cmds[i][j] == '>')
			{
				name = filename(sh->cmds[i] + j);
			}
		}
	}
}