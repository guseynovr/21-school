/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:35:12 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 16:35:12 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	c_src;
	size_t	c_dst;
	size_t	res;

	c_src = ft_strlen(src);
	c_dst = ft_strlen(dst);
	if (c_dst > dstsize)
		res = dstsize + c_src;
	else
		res = c_dst + c_src;
	if (!dst || !src)
		return (0);
	i = 0;
	if (c_dst < dstsize)
	{
		while (c_dst < dstsize - 1 && src[i])
			dst[c_dst++] = src[i++];
		dst[c_dst] = 0;
	}
	return (res);
}
