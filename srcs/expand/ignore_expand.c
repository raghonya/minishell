/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignore_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:10:49 by raghonya          #+#    #+#             */
/*   Updated: 2023/06/05 15:11:31 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	remove_single_quote(char *line)
{
	int	i;
	int	j;

	i = 0;
	while (line[i])
	{
		if (line[i] && line[i + 1] && line[i] == '<' && line[i + 1] == '<')
		{
			j = i + 2;
			while (line[j] && ft_isspace(line[j]))
				j++;
			while (line[j + 1] && !(line[j + 1] == '\'' && line[j + 2] == '\v'))
			{
				line[j] = line[j + 1];
				j++;
			}
			i = --j;
			while (line[++j + 3])
				line[j] = line[j + 3];
			line[j] = 0;
		}
		i++;
	}
}

char	*new_string(char *line, int start, int end)
{
	char	*new;
	int		j;
	int		k;

	new = malloc(sizeof(char) * (ft_strlen(line) + 4));
	err_msg_w_exit(!new, 1);
	j = 0;
	k = 0;
	while (j < start)
		new[k++] = line[j++];
	new[k++] = '\'';
	while (j < end)
		new[k++] = line[j++];
	new[k++] = '\'';
	new[k++] = '\v';
	while (line[j])
		new[k++] = line[j++];
	new[k] = 0;
	free(line);
	return (new);
}

char	*heredoc_change(char *line)
{
	int		start_ind;
	int		end_ind;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] && line[i + 1] && line[i] == '<' && line[i + 1] == '<')
		{
			i += 2;
			while (line[i] && ft_isspace(line[i]))
				i++;
			start_ind = i;
			while (line[i] && !ft_isspace(line[i]) \
			&& line[i] != '<' && line[i] != '>')
				ignore_quotes(line, &i);
			end_ind = i;
			line = new_string(line, start_ind, end_ind);
		}
		i++;
	}
	return (line);
}
