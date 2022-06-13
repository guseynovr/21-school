/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:34:56 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 16:34:57 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*new_b;
	size_t	i;

	i = 0;
	new_b = (char *) b;
	while (i < len)
		new_b[i++] = (unsigned char) c;
	return (b);
}
