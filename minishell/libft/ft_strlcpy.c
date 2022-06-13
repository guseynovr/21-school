/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 15:25:12 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/03 15:25:12 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!src)
		return (0);
	if (!dst || !dstsize)
		return (ft_strlen(src));
	i = -1;
	while (++i < dstsize - 1 && src[i])
		dst[i] = src[i];
	if (i < dstsize)
		dst[i] = 0;
	return (ft_strlen(src));
}
