/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:34:49 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 16:34:50 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*new_s;
	unsigned char	new_c;

	i = 0;
	new_c = (unsigned char) c;
	new_s = (unsigned char *) s;
	while (i < n)
	{
		if (new_s[i] == new_c)
			return (new_s + i);
		i++;
	}
	new_s = 0;
	return (new_s);
}
