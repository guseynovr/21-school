#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	uc;
	unsigned char	*s_ch;

	s_ch = (unsigned char *) s;
	uc = (unsigned char) c;
	i = -1;
	while (++i < n)
		if (s_ch[i] == uc)
			return ((void *)(s + i));
	return (0);
}
