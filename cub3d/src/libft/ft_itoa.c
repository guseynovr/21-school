/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:34:10 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 16:34:11 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_str(int n)
{
	int	i;

	if (!n)
		return (1);
	i = 0;
	if (n < 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*res;
	char	c;
	int		len_res;

	len_res = len_str(n);
	res = malloc(sizeof(char) * (len_res + 1));
	if (!res)
		return (0);
	if (!n)
		res[0] = '0';
	res[len_res] = 0;
	if (n < 0)
		res[0] = '-';
	while (n)
	{
		if (n < 0)
			c = ((n % 10) * -1) + '0';
		else
			c = n % 10 + '0';
		n /= 10;
		res[--len_res] = c;
	}
	return (res);
}
