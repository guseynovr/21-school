#include "get_next_line.h"

size_t	ft_strl(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (*s && *s++ != '\n')
		i++;
	return (i);
}

char	*ft_strjn(char *s1, char *s2, int *nl)
{
	char	*new;
	size_t	new_len;
	int		i;

	*nl = -1;
	if (!s1 && !s2)
		return (0);
	new_len = ft_strl(s1) + ft_strl(s2);
	new = malloc(new_len + 1);
	if (!new)
		return (0);
	i = -1;
	if (ft_strl(s1) > 0)
		while (s1[++i])
			*new++ = s1[i];
	free(s1);
	i = -1;
	while (s2[++i] && s2[i] != '\n')
		*new++ = s2[i];
	if (s2[i] == '\n')
		*nl = i;
	*new = 0;
	return (new -= new_len);
}
