/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:35:05 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 16:35:05 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr_one(const char *s, int c)
{
	char	new_c;
	size_t	i;
	size_t	c_s;

	i = 0;
	c_s = ft_strlen(s) + 1;
	new_c = (char) c;
	while (i < c_s)
	{
		if (s[i] == new_c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	char	new_c;
	size_t	i;
	size_t	c_s;

	i = 0;
	c_s = ft_strlen(s) + 1;
	new_c = (char) c;
	while (i < c_s)
	{
		if (s[i] == new_c)
			return ((char *)s + i);
		i++;
	}
	return (0);
}
