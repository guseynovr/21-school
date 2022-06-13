/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 15:24:29 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/03 15:24:30 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*d_ch;
	char	*s_ch;

	if (!dst && !src)
		return (0);
	d_ch = (char *) dst;
	s_ch = (char *) src;
	if (dst < src)
	{
		i = -1;
		while (++i < len)
			d_ch[i] = s_ch[i];
	}
	else
		while (len--)
			d_ch[len] = s_ch[len];
	return (dst);
}
