/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 15:24:56 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/03 15:24:58 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	cc;

	i = -1;
	cc = (char) c;
	while (s[++i])
		if (s[i] == cc)
			return ((char *)(s + i));
	if (s[i] == c)
		return ((char *)(s + i));
	return (0);
}
