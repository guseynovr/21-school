#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	s_len;
	char	*dup;

	s_len = ft_strlen(s1);
	dup = malloc(s_len + 1);
	if (!dup)
		return (0);
	while (*s1)
		*dup++ = *s1++;
	*dup = 0;
	return (dup - s_len);
}
