/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:35:00 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 16:35:01 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	r_ft_putnmbr(int n, char sign, int fd)
{
	char	c;

	if (n == 0)
		return ;
	r_ft_putnmbr(n / 10, sign, fd);
	c = n % 10;
	if (sign == '-')
		c *= -1;
	c += '0';
	ft_putchar_fd(c, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	sign;

	if (n == 0)
		write(fd, "0", 1);
	sign = '+';
	if (n < 0)
	{
		write(fd, "-", 1);
		sign = '-';
	}
	r_ft_putnmbr(n, sign, fd);
}
