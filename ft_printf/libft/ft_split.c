#include "libft.h"

static	size_t	count_size(char const *s, char c)
{
	size_t	size;
	int		len;

	size = 0;
	len = 0;
	while (*s)
	{
		if (*s == c && len > 0)
		{
			size++;
			len = 0;
		}
		else if (*s != c)
			len++;
		s++;
	}
	if (len > 0)
		size++;
	return (size);
}

static char	*mstr(char const *s, int len)
{
	char	*str;
	int		i;

	str = malloc(len + 1);
	if (!str)
		return (0);
	i = -1;
	while (++i < len)
		str[i] = s[i];
	str[i] = 0;
	return (str);
}

static void	*free_memory(char **splitted, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(splitted[i]);
		splitted[i++] = 0;
	}
	free(splitted);
	splitted = 0;
	return (0);
}

static int	new_str(char const *s, char **splitted, size_t i, int *len)
{
	splitted[i] = mstr(s - *len, *len);
	if (!splitted[i])
		return ((int) free_memory(splitted, i - 1));
	*len = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**splitted;
	size_t	i;
	int		len;

	if (!s)
		return (0);
	splitted = malloc(sizeof(char *) * (count_size(s--, c) + 1));
	if (!splitted)
		return (0);
	len = 0;
	i = 0;
	while (*++s)
	{
		if (*s == c && len > 0 && !new_str(s, splitted, i++, &len))
			return (0);
		else if (*s != c)
			len++;
	}
	if (len > 0 && !new_str(s, splitted, i++, &len))
		return (0);
	splitted[i] = 0;
	return (splitted);
}
