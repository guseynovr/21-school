#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	src_len = ft_strlen(src);
	if (!dstsize)
		return (src_len);
	i = ft_strlen(dst);
	if (i < dstsize)
		dst_len = i;
	else
		dst_len = dstsize;
	while (i < dstsize - 1 && *src)
		dst[i++] = *src++;
	if (dst_len < dstsize)
		dst[i] = 0;
	return (src_len + dst_len);
}
