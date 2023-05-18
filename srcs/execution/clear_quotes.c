/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 17:11:45 by raghonya          #+#    #+#             */
/*   Updated: 2023/05/13 17:11:46 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	clear_quotes_matrix(char **line)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (line[++i])
	{
		j = -1;
		while (line[i][++j])
		{
			if (line[i][j] && (line[i][j] == '\"' || line[i][j] == '\''))
			{
				k = j - 1;
				j = line[i][j];
				while (line[i][++k + 1] != j)
					line[i][k] = line[i][k + 1];
				j = k-- - 1;
				while (line[i][++k + 2])
					line[i][k] = line[i][k + 2];
				line[i][k] = 0;
			}
		}
	}
}

void	clear_quotes_line(char *line)
{
	int	i;
	int	k;

	i = -1;
	while (line[++i])
	{
		if (line[i] && (line[i] == '\"' || line[i] == '\''))
		{
			k = i - 1;
			i = line[i];
			while (line[++k + 1] != i)
				line[k] = line[k + 1];
			i = k-- - 1;
			while (line[++k + 2])
				line[k] = line[k + 2];
			line[k] = 0;
		}
	}
}
