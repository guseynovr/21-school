/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:35:18 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 16:35:19 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	char	*new_dst;
	char	*new_src;
	size_t	c_src;

	if (!src || !dst)
		return (0);
	c_src = 0;
	while (src[c_src])
		c_src++;
	if (dstsize == 0)
		return (c_src);
	new_dst = (char *)dst;
	new_src = (char *)src;
	i = 0;
	while ((i < dstsize - 1) && (src[i]))
	{
		new_dst[i] = new_src[i];
		i++;
	}
	new_dst[i] = 0;
	if (i > c_src)
		return (i);
	return (c_src);
}
