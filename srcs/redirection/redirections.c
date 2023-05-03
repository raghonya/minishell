/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:09:44 by raghonya          #+#    #+#             */
/*   Updated: 2023/05/01 13:09:49 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*filename(char *str)
{
	char	*name;
	int		i;

	// printf ("str do <>: %s\n", str);
	i = -1;
	while (ft_isspace(str[++i]))
		;
	str += ++i;
	// printf ("str after <>: %s\n", str);
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
	// printf ("name of the file: %s\n", name);
	return (name);
}

// check filename, arajin elementy inch kara lini

char	*find_filename(char *line)
{
	char	*redir;
	char	*tmp;
	int		aft_spc;
	int		i;

	i = -1;
	while (ft_isspace(line[++i]))
		;
	aft_spc = i;
	while (line[i] && (line[i] == '_' || \
		line[i] == '.' || line[i] == '-' || ft_isalnum(line[i])))
		i++;
	redir = ft_substr(line, aft_spc, i - aft_spc);
	tmp = redir;
	redir = ft_strtrim(redir, " \t\n\r\v\f");
	// printf ("aft trim: '%s'\n", redir);
	free(tmp);
	return (redir);
}

int	heredoc_or_append(t_shell *sh, char *line, int i)
{
	char	*redir;

	redir = find_filename(line + i + 1);
	clear_quotes_line(redir);
	printf ("heredoc/append:,,,%s,,,\n", redir);
	return (0);
}

int	redirect_io(t_shell *sh, char *line, int i)
{
	char	*redir;

	redir = find_filename(line + i + 1);
	clear_quotes_line(redir);
	printf ("filename:`%s`\n", redir);
	if (line[i] == '<')
	{
		sh->fdin = open(redir, O_RDONLY);
		// printf ("filename%s\n", redir);
		free(redir);
		if (err_msg (sh->fdin == -1, "No such file or directory"))
			return (1);
	}
	else
	{
		sh->fdout = open(redir, O_WRONLY | O_CREAT | O_TRUNC);
		free(redir);
		if (err_msg (sh->fdout == -1, "No such file or directory"))
			return (1);
	}
	return (0);
}

int	check_redirections(t_shell *sh, char *line)
{
	// char	*name;
	int		i;

	i = -1;
	// printf ("line wthout quotes: %s\n", line);
	while (line[++i])
	{
		if (line[i] == '<' || line[i] == '>')
		{
			if (err_msg((line[i] == '<' && line[i + 1] == '>') \
				|| (line[i] == '>' && line[i + 1] == '<'), \
				"Syntax error"))
					return (1);
			if (line[i + 1] == line[i])
			{
				if (heredoc_or_append(sh, line, ++i))
					return (1);
			}
			else
			{
				if (redirect_io(sh, line, i))
					return (1);
			}
		}
	}
	free(line);
	return (0);
}
