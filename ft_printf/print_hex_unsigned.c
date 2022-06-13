#include "ft_printf.h"

static void	process_wpt(t_format *format, int *zero)
{
	if (format->dot && !format->value.ulli && !format->precision)
		*zero = 1;
	if (*zero)
		format->value_l = 0;
	format->total += format->value_l;
	format->precision -= format->value_l;
	if (format->precision > 0)
		format->total += format->precision;
}

void	print_unsigned(t_format *format)
{
	int	i;
	int	zero;

	zero = 0;
	format->value_l = unsigned_len(format->value.ulli);
	process_wpt(format, &zero);
	i = format->total;
	if (format->width > format->total)
		format->total = format->width;
	while (!format->left && format->width-- > i)
		write(1, &format->padding, 1);
	while (format->precision-- > 0)
		write(1, "0", 1);
	if (!zero)
		ft_putnbr_unsigned(format->value.ulli);
	while (format->left && format->width-- > i)
		write(1, &format->padding, 1);
}

static void	prepare_hex_format(t_format *format, char **base, char **alt)
{
	if (format->alt_form && format->specifier == 'X')
		*alt = "0X";
	else if (format->alt_form || format->specifier == 'p')
		*alt = "0x";
	if (*alt)
		format->total += 2;
	if (format->specifier == 'X')
		*base = "0123456789ABCDEF";
	else
		*base = "0123456789abcdef";
}

void	print_hex(t_format *format)
{
	char	*base;
	char	*alt;
	int		i;
	int		zero;

	alt = 0;
	base = 0;
	zero = 0;
	prepare_hex_format(format, &base, &alt);
	format->value_l = hex_len(format->value.ulli);
	process_wpt(format, &zero);
	i = format->total;
	if (format->width > format->total)
		format->total = format->width;
	while (!format->left && format->width-- > i)
		write(1, &format->padding, 1);
	write(1, alt, 2);
	while (format->precision-- > 0)
		write(1, "0", 1);
	if (!zero)
		ft_putnbr_hex(format->value.ulli, base);
	while (format->left && format->width-- > i)
		write(1, &format->padding, 1);
}
