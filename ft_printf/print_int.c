#include "ft_printf.h"

static void	print_sign(t_format *format)
{
	if (format->value.i >= 0 && format->sign)
	{
		write(1, &format->sign, 1);
		format->total++;
	}
	else if (format->value.i < 0)
	{
		write(1, "-", 1);
		format->total++;
	}
}

int	int_len(long long int n)
{
	int	l;

	if (!n)
		return (1);
	l = 0;
	while (n)
	{
		n /= 10;
		l++;
	}
	return (l);
}

static void	print_int_precision(t_format *format)
{
	int	i;

	i = format->precision;
	if (format->padding != '0')
		print_sign(format);
	if (format->value_l < format->precision)
	{
		while (i-- > format->value_l)
		{
			write(1, "0", 1);
			format->total++;
		}
	}
	if (format->dot && !format->precision && !format->value.i)
	{
		format->total--;
		if (format->width > 0)
		{
			write(1, &format->padding, 1);
			format->total++;
		}
	}
	else
		ft_putnbr_nosign(format->value.i);
}

void	print_int(t_format *format)
{
	int	i;

	i = -1;
	format->value_l = int_len(format->value.i);
	if (!format->value.i && format->dot && !format->precision)
		format->value_l = 0;
	format->total = format->value_l;
	if (format->value.i < 0 || format->sign)
		format->width--;
	format->width -= format->value_l;
	if (format->padding == '0')
		print_sign(format);
	if (format->precision > format->value_l)
		format->width -= format->precision - format->value_l;
	if (format->width > 0)
		format->total += format->width;
	while (!format->left && ++i < format->width)
		write(1, &format->padding, 1);
	if (!(!format->value.i && format->dot && !format->precision))
		print_int_precision(format);
	while (format->left && ++i < format->width)
		write(1, &format->padding, 1);
}
