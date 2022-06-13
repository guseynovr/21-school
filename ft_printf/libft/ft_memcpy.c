#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dst_ch;
	char	*src_ch;

	if (!dst && !src)
		return (0);
	dst_ch = (char *)dst;
	src_ch = (char *)src;
	i = -1;
	while (++i < n)
		dst_ch[i] = src_ch[i];
	return (dst);
}
