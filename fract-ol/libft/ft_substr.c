#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	size_t	substr_len;
	char	*substring;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (start < s_len && len < s_len - start)
		substr_len = len;
	else if (start < s_len)
		substr_len = s_len - start;
	else
		substr_len = 0;
	substring = malloc(substr_len + 1);
	if (!substring)
		return (0);
	i = -1;
	while (s[++i + start] && i < substr_len)
		substring[i] = s[i + start];
	substring[i] = 0;
	return (substring);
}
