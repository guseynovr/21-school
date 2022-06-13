/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:34:51 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 16:35:53 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*new_s1;
	unsigned char	*new_s2;

	i = 0;
	new_s1 = (unsigned char *) s1;
	new_s2 = (unsigned char *) s2;
	while (i < n)
	{
		if (new_s1[i] - new_s2[i])
			return (new_s1[i] - new_s2[i]);
		i++;
	}
	return (0);
}
