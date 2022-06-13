/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 15:23:47 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/03 15:23:47 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_size(int n)
{
	int	size;

	if (n == 0)
		return (1);
	size = 0;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		size;
	int		sign;

	size = count_size(n);
	if (n < 0)
		size++;
	s = malloc(size + 1);
	if (!s)
		return (0);
	sign = 1;
	if (n < 0)
	{
		*s = '-';
		sign = -1;
	}
	s[size] = 0;
	if (!n)
		*s = '0';
	while (n)
	{
		s[--size] = (n % 10) * sign + '0';
		n /= 10;
	}
	return (s);
}
