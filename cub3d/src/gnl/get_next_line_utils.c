/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:33:41 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 16:33:42 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlena(const char *s)
{
	int	k;

	if (!s)
		return (0);
	k = 0;
	while (s[k])
		k++;
	return (k);
}

int	check_n(char *s)
{
	if (!s)
		return (0);
	while (*s)
		if (*s++ == '\n')
			return (1);
	return (0);
}

void	move_buf(char **buf, int i)
{
	int	k;

	k = 0;
	while ((*buf)[i++])
		(*buf)[k++] = (*buf)[i];
}

char	*check_buf(char *buf, char *line, int *flg)
{
	int		i;
	char	*res;

	*flg = 0;
	if (!*buf)
		return (0);
	if (!check_n(buf))
		return (ft_strjoina(line, buf));
	*flg = 1;
	i = 0;
	while (buf[i] != '\n')
		i++;
	buf[i] = 0;
	res = ft_strjoina(line, buf);
	buf[i] = '\n';
	move_buf(&buf, i);
	return (res);
}

char	*ft_strjoina(char const *s1, char const *s2)
{
	char	*res;
	size_t	i;
	int		k;
	int		len_s1;
	int		len_s2;

	if (!s1 && !s2)
		return (0);
	len_s1 = ft_strlena((char *)s1);
	len_s2 = ft_strlena((char *)s2);
	i = len_s1 + len_s2;
	res = malloc(i + 1);
	if (!res)
		return (0);
	k = 0;
	while (len_s1-- > 0)
		*res++ = s1[k++];
	while (len_s2-- > 0)
		*res++ = *s2++;
	*res = 0;
	free((char *)s1);
	return (res - i);
}
