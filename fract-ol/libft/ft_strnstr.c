#include "libft.h"

static int	test_occurrence(const char *h, const char *n, size_t left_space)
{
	size_t	n_len;

	n_len = ft_strlen(n);
	if (left_space < n_len || ft_strlen(h) < n_len)
		return (0);
	while (*h && *n)
		if (*h++ != *n++)
			return (0);
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	char	*occurrence;
	size_t	offset;

	if (!*needle)
		return ((char *)(haystack));
	i = -1;
	occurrence = ft_strchr(haystack + ++i, *needle);
	while (occurrence)
	{
		offset = occurrence - haystack;
		if (offset > len)
			return (0);
		if (test_occurrence(occurrence, needle, len - offset))
			return (occurrence);
		occurrence = ft_strchr(haystack + ++i, *needle);
	}
	return (0);
}
