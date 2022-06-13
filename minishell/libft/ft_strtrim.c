/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 15:25:31 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/03 15:25:32 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	size_t	new_len;
	size_t	start;
	size_t	end;

	if (!s1)
		return (0);
	start = 0;
	while (ft_strchr(set, s1[start]) && s1[start])
		start++;
	end = ft_strlen(s1) - 1;
	if (!*s1)
		end++;
	while (ft_strchr(set, s1[end]) && end > start)
		end--;
	new_len = ++end - start;
	if (end < start)
		new_len = 0;
	new = malloc(new_len + 1);
	if (!new)
		return (0);
	new[new_len] = 0;
	while (start < end)
		*new++ = s1[start++];
	return (new - new_len);
}
