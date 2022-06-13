/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 15:25:00 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/03 15:25:01 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	s_len;
	char	*dup;

	s_len = ft_strlen(s1);
	dup = malloc(s_len + 1);
	if (!dup)
		return (0);
	while (*s1)
		*dup++ = *s1++;
	*dup = 0;
	return (dup - s_len);
}
