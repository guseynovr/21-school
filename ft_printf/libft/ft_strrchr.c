#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	cc;
	size_t	len;

	cc = (char) c;
	len = ft_strlen(s) + 1;
	while (len-- > 0)
		if (s[len] == c)
			return ((char *)(s + len));
	return (0);
}
