#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define FLAGS "-0+ #"
# define ALLMOD "-0+ #lh"
# define SPECIFIERS "cspdiuxX%"
# define SP_COUNT 9
# define NULL_STR "(null)"
# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

typedef union u_value
{
	signed char				sc;
	short int				si;
	int						i;
	long int				li;
	long long int			lli;
	unsigned char			uc;
	unsigned short int		usi;
	unsigned int			ui;
	unsigned long int		uli;
	unsigned long long int	ulli;
	double					d;
	wchar_t					lc;
	char					*s;
	wchar_t					*ls;
	void					*p;
}	t_value;

typedef struct s_format
{
	int		left;
	char	padding;
	char	sign;
	char	alt_form;
	int		width;
	int		precision;
	int		dot;
	int		length;
	char	specifier;
	int		value_l;
	int		total;
	t_value	value;
	int		len;
}	t_format;

int		ft_printf(const char *format, ...);
char	*parse_specifier(char *s, t_format *format, va_list val);
void	print_specifier(t_format *format, va_list val);
int		calc_width(t_format *format);
void	ft_putnbr_nosign(long long int n);
void	ft_putnbr_unsigned(unsigned long long int n);
int		int_len(long long int n);
void	ft_putnbr_hex(unsigned long long int n, char *base);
int		hex_len(unsigned long long int n);
int		unsigned_len(unsigned long long int n);
void	print_int(t_format *format);
void	print_hex(t_format *format);
void	print_unsigned(t_format *format);
#endif
