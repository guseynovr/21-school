/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 15:25:27 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/03 15:25:28 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	cc;
	size_t	len;

	cc = (char) c;
	len = ft_strlen(s) + 1;
	while (len-- > 0)
		if (s[len] == c)
			return ((char *)(s + len));
	return (0);
}
