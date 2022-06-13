/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:35:30 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 16:35:31 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	new_c;
	size_t	c_s;

	c_s = ft_strlen(s) + 1;
	new_c = (char) c;
	while (c_s-- > 0)
	{
		if (s[c_s] == new_c)
			return ((char *)s + c_s);
	}
	return (0);
}
