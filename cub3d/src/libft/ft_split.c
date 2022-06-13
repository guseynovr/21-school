/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:35:04 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 16:35:04 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_strs(const char *s, char c)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			res++;
			i++;
		}
		while (s[i] != c && s[i])
			i++;
	}
	if (!res)
		return (1);
	return (res);
}

static char	*get_str(char **s, char c)
{
	size_t	i;
	size_t	len_str;
	char	*res;

	i = 0;
	len_str = 0;
	while (**s == c && *(*s)++)
		i++;
	while (**s != c && **s)
	{
		len_str++;
		(*s)++;
	}
	res = malloc(sizeof(char) * (len_str + 1));
	if (!res)
		return (0);
	ft_strlcpy(res, *s - len_str, (len_str + 1));
	return (res);
}

static char	**free_malloc(char **res)
{
	int	i;

	i = 0;
	while (res[i])
		free(res[i++]);
	free(res);
	return (0);
}

char	**ft_split(const char *s, char c)
{
	char	**res;
	size_t	len_res;
	size_t	i;

	if (!s)
		return (0);
	len_res = count_strs(s, c);
	while (*s == c && *s)
		s++;
	if (!(*s))
		return (ft_calloc(1, sizeof(char *) * 1));
	res = malloc(sizeof(char *) * (len_res + 1));
	if (!res)
		return (0);
	i = 0;
	while (i < len_res)
	{
		res[i] = get_str((char **) &s, c);
		if (!res[i])
			return (free_malloc(res));
		i++;
	}
	res[i] = 0;
	return (res);
}
