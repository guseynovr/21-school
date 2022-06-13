/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:33:39 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 16:33:39 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static char		buf[BUFFER_SIZE + 1];
	int				read_b;
	int				flg;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	*line = 0;
	*line = check_buf(buf, *line, &flg);
	read_b = 1;
	while (read_b && !flg)
	{
		read_b = (int)read(fd, buf, BUFFER_SIZE);
		if (read_b < 0)
			return (-1);
		buf[read_b] = 0;
		if (!(check_n(buf)))
			*line = ft_strjoina(*line, buf);
		else
			*line = check_buf(buf, *line, &flg);
	}
	if (read_b == 0)
		return (0);
	return (1);
}
