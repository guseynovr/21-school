/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 15:25:02 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/03 15:25:03 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	new_len;
	char	*new;

	if (!s1 || !s2)
		return (0);
	new_len = ft_strlen(s1) + ft_strlen(s2);
	new = malloc(new_len + 1);
	if (!new)
		return (0);
	while (*s1)
		*new++ = *s1++;
	while (*s2)
		*new++ = *s2++;
	*new = 0;
	return (new - new_len);
}
