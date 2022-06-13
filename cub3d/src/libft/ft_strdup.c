/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:35:06 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 16:35:07 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*res;
	int		c_s1;

	c_s1 = ft_strlen(s1);
	res = malloc(c_s1 + 1);
	if (!res)
		return (0);
	while (*s1)
		*res++ = *s1++;
	*res = 0;
	return (res - c_s1);
}
