#include "ft_printf.h"

void	ft_putnbr_nosign(long long int n)
{
	char	nbr[19];
	int		sign;
	int		len;
	int		i;

	sign = 1;
	if (!n)
	{
		write(1, "0", 1);
		return ;
	}
	if (n < 0)
		sign = -1;
	len = int_len(n);
	i = len;
	ft_bzero(nbr, 19);
	while (n)
	{
		nbr[--i] = (n % 10) * sign + '0';
		n /= 10;
	}
	write(1, nbr, len);
}

void	ft_putnbr_unsigned(unsigned long long int n)
{
	char	nbr[19];
	int		len;
	int		i;

	if (!n)
	{
		write(1, "0", 1);
		return ;
	}
	len = int_len(n);
	i = len;
	ft_bzero(nbr, 19);
	while (n)
	{
		nbr[--i] = (n % 10) + '0';
		n /= 10;
	}
	write(1, nbr, len);
}

int	unsigned_len(unsigned long long int n)
{
	int	len;

	if (!n)
		return (1);
	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	hex_len(unsigned long long int n)
{
	int	len;

	if (!n)
		return (1);
	len = 0;
	while (n)
	{
		n /= 16;
		len++;
	}
	return (len);
}

void	ft_putnbr_hex(unsigned long long int n, char *base)
{
	char	hex[16];
	int		i;
	int		len;

	if (!n)
	{
		write(1, "0", 1);
		return ;
	}
	ft_bzero(hex, 16);
	len = hex_len(n);
	i = len;
	while (n)
	{
		hex[--i] = base[n % 16];
		n /= 16;
	}
	write(1, hex, len);
}
