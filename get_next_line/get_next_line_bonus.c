#include "get_next_line_bonus.h"

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

char	*find_buff(t_blst **lst, int fd)
{
	t_blst	*new;
	t_blst	*head;
	int		i;

	head = *lst;
	while (head)
	{
		if (head->fd == fd)
			return (head->buffer);
		head = head->next;
	}
	new = malloc(sizeof(t_blst));
	if (!new)
		return (0);
	new->next = *lst;
	new->fd = fd;
	i = -1;
	while (++i <= BUFFER_SIZE)
		new->buffer[i] = 0;
	*lst = new;
	return (new->buffer);
}

void	del_elem(t_blst **lst, int fd)
{
	t_blst	*head;
	t_blst	*temp;

	head = *lst;
	temp = 0;
	while (head && (head->fd == fd))
	{
		temp = head->next;
		free(head);
		head = temp;
		*lst = head;
	}
	while (head)
	{
		if (head->fd == fd)
		{
			temp->next = head->next;
			free(head);
			head = temp->next;
			continue ;
		}
		temp = head;
		head = head->next;
	}
}

int	get_next_line(int fd, char **line)
{
	static t_blst	*head;
	char			*buff;
	int				result;

	if (!line || fd < 0 || BUFFER_SIZE < 1)
		return (ERR);
	buff = find_buff(&head, fd);
	if (!buff)
		return (ERR);
	result = next(fd, line, buff);
	if (result < 1)
		del_elem(&head, fd);
	return (result);
}
