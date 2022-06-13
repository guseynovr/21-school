#include "ft_printf.h"

int	print_next(char **next, const char **s, t_format *format, va_list val)
{
	int	len;

	write(1, *s, *next - *s);
	format->len += *next - *s;
	*next = parse_specifier(*next + 1, format, val);
	print_specifier(format, val);
	len = format->len + format->total;
	ft_bzero(format, sizeof(t_format));
	*s = *next;
	*next = ft_strchr(*s, '%');
	return (len);
}

int	ft_printf(const char *s, ...)
{
	va_list		val;
	t_format	format;
	char		*next;

	va_start(val, s);
	ft_bzero(&format, sizeof(t_format));
	next = ft_strchr(s, '%');
	while (next)
		format.len += print_next(&next, &s, &format, val);
	va_end(val);
	format.len += ft_strlen(s);
	write(1, s, ft_strlen(s));
	return (format.len);
}
