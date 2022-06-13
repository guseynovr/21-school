#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	new_len;
	char	*new;

	if (!s1 || !s2)
		return (0);
	new_len = ft_strlen(s1) + ft_strlen(s2);
	new = malloc(new_len + 1);
	if (!new)
		return (0);
	while (*s1)
		*new++ = *s1++;
	while (*s2)
		*new++ = *s2++;
	*new = 0;
	return (new - new_len);
}
