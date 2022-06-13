#include "ft_printf.h"

static void	set_flags(t_format *format, char flag)
{
	if (flag == '-')
		format->left = 1;
	else if (flag == '0' && !format->left)
		format->padding = flag;
	else if (flag == '+')
		format->sign = flag;
	else if (flag == ' ' && !format->sign)
		format->sign = flag;
	else if (flag == '#')
		format->alt_form = flag;
}

static char	*set_field(int *field, char *s, va_list val, t_format *format)
{
	if (*s == '*')
	{
		*field = va_arg(val, int);
		s++;
	}	
	else if (ft_isdigit(*s))
	{
		*field = ft_atoi(s);
		while (ft_isdigit(*s))
			s++;
	}
	if (field == &format->width && *field < 0)
	{
		format->left = 1;
		format->padding = ' ';
		*field *= -1;
	}
	if (field == &format->precision && format->precision >= 0)
		format->padding = ' ';
	return (s);
}

static char	*set_length(t_format *format, char *s)
{
	if (*s == 'h')
	{
		format->length--;
		if (*++s == 'h')
		{
			format->length--;
			s++;
		}
	}
	else if (*s == 'l')
	{
		format->length++;
		if (*++s == 'l')
		{
			format->length++;
			s++;
		}
	}
	return (s);
}

char	*parse_specifier(char *s, t_format *format, va_list val)
{
	if (!s)
		return (0);
	while (*s && ft_strchr(FLAGS, *s))
		set_flags(format, *s++);
	if (!format->padding)
		format->padding = ' ';
	s = set_field(&(format->width), s, val, format);
	if (*s == '.')
	{
		format->dot = 1;
		s = set_field(&(format->precision), s + 1, val, format);
	}
	s = set_length(format, s);
	while (*s && ft_strchr(ALLMOD, *s))
		s++;
	if (*s)
		format->specifier = *s++;
	return (s);
}
