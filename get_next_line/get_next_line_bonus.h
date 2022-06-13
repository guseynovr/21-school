#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# define ERR -1
# define EOFR 0
# define OK 1
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_blst
{
	int				fd;
	char			buffer[BUFFER_SIZE + 1];
	struct s_blst	*next;
}	t_blst;

int		get_next_line(int fd, char **line);
char	*ft_strjoin(char *s1, char *s2, int *nl);
size_t	ft_strlen(const char *s);
#endif
