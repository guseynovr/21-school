#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*s1_c;
	const unsigned char	*s2_c;

	s1_c = (const unsigned char *) s1;
	s2_c = (const unsigned char *) s2;
	i = -1;
	while (++i < n)
		if (s1_c[i] != s2_c[i])
			return (s1_c[i] - s2_c[i]);
	return (0);
}
