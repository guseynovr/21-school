#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	uc;
	unsigned char	*d_ch;
	unsigned char	*s_ch;

	if (!dst && !src)
		return (0);
	d_ch = (unsigned char *) dst;
	s_ch = (unsigned char *) src;
	uc = (unsigned char) c;
	i = -1;
	while (++i < n)
	{	
		d_ch[i] = s_ch[i];
		if (s_ch[i] == uc)
			return (d_ch + i + 1);
	}
	return (0);
}
