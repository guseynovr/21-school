#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*d_ch;
	char	*s_ch;

	if (!dst && !src)
		return (0);
	d_ch = (char *) dst;
	s_ch = (char *) src;
	if (dst < src)
	{
		i = -1;
		while (++i < len)
			d_ch[i] = s_ch[i];
	}
	else
		while (len--)
			d_ch[len] = s_ch[len];
	return (dst);
}
