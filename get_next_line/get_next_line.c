#include "get_next_line.h"

int	update_buffer(char *buff, int nl, int flag)
{
	size_t	i;

	i = 0;
	while (buff[nl++])
		buff[i++] = buff[nl];
	buff[i] = 0;
	return (flag);
}

int	next(int fd, char **line, char *buff)
{
	ssize_t		ret;
	int			nl;

	*line = 0;
	ret = 1;
	while (ret > 0)
	{
		*line = ft_strjoin(*line, buff, &nl);
		if (!*line)
			return (ERR);
		if (nl >= 0)
			return (update_buffer(buff, nl, OK));
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret < BUFFER_SIZE && ret >= 0)
			buff[ret] = 0;
	}
	if (!ret && buff[0])
		return (update_buffer(buff, ft_strlen(buff), EOFR));
	if (ret < 0)
	{
		free(*line);
		*line = 0;
	}
	return (ret);
}

int	get_next_line(int fd, char **line)
{
	static char	buff[BUFFER_SIZE + 1];

	if (!line || fd < 0 || BUFFER_SIZE < 1)
		return (ERR);
	return (next(fd, line, buff));
}
