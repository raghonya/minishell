#include <minishell.h>

int	check_varname(char *s)
{
	if (!ft_isalpha(*s) && *s != '_')
		return (1);
	while (*s && !ft_isspace(*s) && *s != '$' && *s != '\"')
	{
		if (!ft_isdigit(*s) && *s != '_' && !ft_isalpha(*s))
			return (1);
		s++;
	}
	return (0);
}

char	*varname(char *s, int *length)
{
	char	*ret;
	int		i;

	i = 0;
	while (s[i] && !ft_isspace(s[i]) && s[i] != '$' && *s != '\"')
		i++;
	if (check_varname(s))
	{	
		*length = i;
		if (!ft_isalpha(*s) && *s != '_')
			*length = 0;
		return (ft_strdup(""));
	}
	ret = malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (ret);
	i = 0;
	while (s[i] && !ft_isspace(s[i]) && s[i] != '$' && s[i] != '\"')
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

char	*check_env(char *line, t_list *env, int length)
{
	char	*tmp;

	if (!*line && length == 0)
		return ("$");
	while (env->data)
	{
		tmp = until_symb(env->data, "=");
		if (!ft_strcmp(tmp, line))
		{
			free(tmp);
			return (after_symb(env->data, '='));
		}
		free(tmp);
		env = env->next;
	}
	return ("");
}
