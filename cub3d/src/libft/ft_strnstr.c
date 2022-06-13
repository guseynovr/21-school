/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:35:27 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 16:35:28 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *small, size_t len)
{
	size_t	l;
	size_t	k;
	size_t	c_big;

	if (!(*small))
		return ((char *) big);
	c_big = ft_strlen(big);
	l = 0;
	while (l < len && l < c_big)
	{
		k = 0;
		if (big[l] == small[k])
		{
			while (big[l + k] == small[k] && l + k < len)
			{
				k++;
				if (!small[k])
					return ((char *)&big[l]);
			}
		}
		l++;
	}
	return (0);
}
