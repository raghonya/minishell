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

int	redirect(t_shell *sh, char **line, int i)
{
	if ((*line)[i] == '<' || (*line)[i] == '>')
	{
		if (err_msg(((*line)[i] == '<' && (*line)[i + 1] == '>') \
			|| ((*line)[i] == '>' && (*line)[i + 1] == '<'), \
			"Syntax error"))
			return (-1);
		if ((*line)[i + 1] == (*line)[i])
		{
			if (heredoc_or_append(sh, line, i--))
				return (-7);
		}
		else if (redirect_io(sh, line, i--))
			return (-7);
	}
	return (i);
}

int	redirections(t_shell *sh, char **line)
{
	int	i;
	int	k;

	i = 0;
	sh->fdin = 0;
	sh->fdout = 1;
	sh->here_closer = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\"' || (*line)[i] == '\'')
		{
			k = i;
			while ((*line)[++i] != (*line)[k])
				;
			i++;
			continue ;
		}
		i = redirect (sh, line, i);
		if (i++ == -7)
			return (1);
	}
	return (0);
}
