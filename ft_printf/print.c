#include "ft_printf.h"

static void	print_string(t_format *format)
{
	char	*s;

	s = (char *) format->value.p;
	if (!s)
		s = NULL_STR;
	format->value_l = ft_strlen(s);
	if (format->dot && format->precision >= 0
		&& format->precision < format->value_l)
		format->value_l = format->precision;
	if (format->width > format->value_l)
		format->total = format->width;
	else
		format->total = format->value_l;
	format->width -= format->value_l;
	while (!format->left && format->width-- > 0)
		write(1, &format->padding, 1);
	write(1, s, format->value_l);
	while (format->left && format->width-- > 0)
		write(1, &format->padding, 1);
}

static void	print_char(t_format *format)
{
	if (!format->width)
		format->total = 1;
	else
		format->total = format->width--;
	format->value_l = 1;
	while (!format->left && format->width-- > 0)
		write(1, &format->padding, 1);
	write(1, &format->value.i, 1);
	while (format->left && format->width-- > 0)
		write(1, &format->padding, 1);
}

static void	init_func_arr(void (**print_arr)(t_format *))
{
	print_arr[0] = print_char;
	print_arr[1] = print_string;
	print_arr[2] = print_hex;
	print_arr[3] = print_int;
	print_arr[4] = print_int;
	print_arr[5] = print_unsigned;
	print_arr[6] = print_hex;
	print_arr[7] = print_hex;
	print_arr[8] = print_char;
}

void	get_value(t_format *f, va_list val)
{
	if (!f->specifier)
		return ;
	else if (ft_strchr("iduxX", f->specifier) && f->length < 1)
		f->value.i = va_arg(val, int);
	else if (ft_strchr("iduxX", f->specifier) && f->length == 1)
		f->value.li = va_arg(val, long int);
	else if (ft_strchr("iduxX", f->specifier) && f->length == 2)
		f->value.lli = va_arg(val, long long int);
	else if (f->specifier == 'd')
		f->value.li = va_arg(val, double);
	else if (f->specifier == 'c' && !f->length)
		f->value.i = va_arg(val, int);
	else if (f->specifier == 'c' && f->length == 1)
		f->value.lc = va_arg(val, wchar_t);
	else if (f->specifier == 's' && !f->length)
		f->value.s = va_arg(val, char *);
	else if (f->specifier == 's' && f->length == 1)
		f->value.ls = va_arg(val, wchar_t *);
	else if (f->specifier == 'p' || f->specifier == 'n' || f->specifier == 's')
		f->value.p = va_arg(val, void *);
	else if (f->specifier == '%')
		f->value.i = f->specifier;
}

void	print_specifier(t_format *format, va_list val)
{
	void	(*print_arr[SP_COUNT])(t_format *);
	char	*sp_ptr;
	char	*spec;

	if (!format->specifier)
		return ;
	spec = SPECIFIERS;
	get_value(format, val);
	init_func_arr(print_arr);
	sp_ptr = ft_strchr(spec, format->specifier);
	if (!sp_ptr)
		return ;
	print_arr[sp_ptr - SPECIFIERS](format);
}
