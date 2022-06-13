/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:34:47 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 16:34:48 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;
	char	*new_dst;
	char	*new_src;
	char	new_c;

	i = 0;
	new_dst = (char *) dst;
	new_src = (char *) src;
	new_c = (char) c;
	while (i < n)
	{
		new_dst[i] = new_src[i];
		if (new_src[i] == new_c)
			return (new_dst + (i + 1));
		i++;
	}
	new_dst = 0;
	return (new_dst);
}
