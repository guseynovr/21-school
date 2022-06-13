/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:34:53 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 16:34:53 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*new_dst;
	char	*new_src;
	size_t	i;

	if (!dst && !src)
		return (0);
	i = 0;
	new_dst = (char *) dst;
	new_src = (char *) src;
	while (i < n)
	{
		new_dst[i] = new_src[i];
		i++;
	}
	return (dst);
}
