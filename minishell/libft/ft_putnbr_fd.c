/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 15:24:48 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/03 15:24:49 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	put_number(int n, int sign, int fd)
{
	if (n == 0)
		return ;
	put_number(n / 10, sign, fd);
	ft_putchar_fd(((n % 10) * sign) + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	sign;

	sign = 1;
	if (!n)
		write(fd, "0", 1);
	if (n < 0)
	{
		write(fd, "-", 1);
		sign = -1;
	}
	put_number(n, sign, fd);
}
