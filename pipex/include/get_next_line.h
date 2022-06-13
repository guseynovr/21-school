#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define ERR -1
# define EOFR 0
# define OK 1
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

int		get_next_line(int fd, char **line);
char	*ft_strjn(char *s1, char *s2, int *nl);
size_t	ft_strl(const char *s);
#endif
