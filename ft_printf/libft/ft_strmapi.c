#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			size;
	char			*new;
	unsigned int	i;

	if (!s)
		return (0);
	size = ft_strlen(s);
	new = malloc(size + 1);
	if (!new)
		return (0);
	new[size] = 0;
	i = -1;
	while (s[++i])
		new[i] = f(i, s[i]);
	return (new);
}
