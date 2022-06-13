#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*us1;
	unsigned char	*us2;

	if (!n)
		return (0);
	us1 = (unsigned char *) s1;
	us2 = (unsigned char *) s2;
	i = 0;
	while (i < n - 1 && us1[i] && us1[i] == us2[i])
		i++;
	return (us1[i] - us2[i]);
}
