#include <minishell.h>

void	clear_quotes_matrix(char **lines)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (lines[++i])
	{
		j = -1;
		while (lines[i][++j])
		{
			if (lines[i][j] && (lines[i][j] == '\"' || lines[i][j] == '\''))
			{
				k = j - 1;
				j = lines[i][j];
				while (lines[i][++k + 1] != j)
					lines[i][k] = lines[i][k + 1];
				j = k-- - 1;
				while (lines[i][++k + 2])
					lines[i][k] = lines[i][k + 2];
				lines[i][k] = 0;
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
