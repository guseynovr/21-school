/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:34:54 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 16:34:55 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*new_dst;
	char	*new_src;

	if (!dst && !src)
		return (0);
	i = 0;
	new_dst = (char *) dst;
	new_src = (char *) src;
	if (new_dst > new_src)
		while (len--)
			new_dst[len] = new_src[len];
	else
	{
		while (i < len)
		{
			new_dst[i] = new_src[i];
			i++;
		}
	}
	return (dst);
}
