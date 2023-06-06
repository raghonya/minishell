
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
