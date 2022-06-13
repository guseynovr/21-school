#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	a;
	char			*casted;

	casted = (char *) b;
	a = (unsigned char) c;
	i = -1;
	while (++i < len)
		casted[i] = a;
	return (b);
}
