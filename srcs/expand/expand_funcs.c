/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:12:07 by raghonya          #+#    #+#             */
/*   Updated: 2023/04/18 20:12:08 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	find_dollar(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

char	*until_symb(char *s, char *c)
{
	char	*ret;
	int		i;

	i = 0;
	while (!ft_strchr(c, s[i]))
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (ret);
	i = 0;
	while (!ft_strchr(c, *s))
		ret[i++] = *s++;
	ret[i] = 0;
	return (ret);
}

char	*after_symb(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c)
		i++;
	i++;
	return (s + i);
}

char	*strjoin_w_free(char*s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	int		i;
	int		k;
	char	*s;

	if (!s1)
		return (ft_strdup(s2));
	i = -1;
	k = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s = malloc (sizeof(char) * (len1 + len2 + 1));
	if (!s)
		return (s);
	while (++i < (int)(len1 + len2))
	{
		if (i < (int)len1)
			s[i] = s1[i];
		else
			s[i] = s2[k++];
	}
	s[i] = 0;
	free(s1);
	return (s);
}
