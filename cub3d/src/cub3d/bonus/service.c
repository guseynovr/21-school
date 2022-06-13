/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 12:46:35 by aarson            #+#    #+#             */
/*   Updated: 2021/11/01 12:21:43 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3d.h"
#include "get_next_line.h"
#include "libft.h"
#include "parse.h"
#include <stdio.h>

int	init_map(t_map **map)
{
	*map = malloc(sizeof(t_map));
	if (!(*map))
		return (0);
	ft_bzero(*map, sizeof(t_map));
	return (1);
}

void	ft_err(char *message)
{
	printf("Error\n");
	printf("%s\n", message);
	exit(1);
}

int	check_open(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_err("Open file, bad path");
	close(fd);
	return (1);
}

int	check_ext(char *path, char *ext)
{
	char	*l_sl;
	int		i;

	check_open(path);
	i = 0;
	l_sl = path;
	while (path[i])
	{
		l_sl = ft_strchr(&path[i], '/');
		if (!l_sl)
		{
			l_sl = &path[i];
			break ;
		}
		l_sl++;
		i = (l_sl - &path[0]);
	}
	if (ft_strlen(l_sl) > ft_strlen(ext))
		if (!(ft_strncmp(&l_sl[ft_strlen(l_sl) - ft_strlen(ext)],
					ext, ft_strlen(l_sl))))
			return (1);
	return (0);
}
