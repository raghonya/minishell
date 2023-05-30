/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:09:05 by raghonya          #+#    #+#             */
/*   Updated: 2023/05/01 13:09:08 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_varname(char *s)
{
	if (!ft_isalpha(*s) && *s != '_')
		return (1);
	while (*s && (ft_isalnum(*s) || *s == '_'))
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
	if (*s == '?')
		return (ft_strdup("?"));
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
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
	i = -1;
	while (s[++i] && (ft_isalnum(s[i]) || s[i] == '_'))
		ret[i] = s[i];
	ret[i] = 0;
	return (ret);
}

char	*check_env(char *line, t_list *env, int length)
{
	char	*tmp;

	if (!*line && length == 0)
		return ("$");
	while (env)
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
