/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 20:05:27 by aarson            #+#    #+#             */
/*   Updated: 2021/11/01 12:21:40 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3d.h"
#include "get_next_line.h"
#include "libft.h"
#include "parse.h"
#include <stdio.h>

int	len_arr(char **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	free_arr(char **name)
{
	int	i;

	if (!name)
		return ;
	i = -1;
	while (name[++i])
		free(name[i]);
	free(name);
}

void	open_file(char *path, int *fd)
{
	*fd = open(path, O_RDONLY);
	if (*fd < 0)
		ft_err("Open file");
}

void	parse_string(t_map *map, char *line, int *status)
{
	char	**names;
	int		i;

	if (!*line && (*status & START) != START)
		return ;
	if ((*status & MAP) == MAP)
		return (valid_str_map(map, line, status));
	if ((line[0] == 32 || line[0] == 48 || line[0] == 49) && (*status & MAP)
		!= MAP)
		ft_err("Invalid map file, map must be end or incorrect count elements");
	i = -1;
	names = init_names();
	while (names[++i])
	{
		if (ft_strncmp(line, names[i], ft_strlen(names[i])))
			continue ;
		else
		{
			valid_elem_str(map, line, status);
			free_names(names);
			return ;
		}
	}
	free_names(names);
	ft_err("Invalid element string");
}

int	parse_map(t_map *map, char *path)
{
	int		fd;
	int		i;
	int		status;
	char	*line;

	status = 0;
	line = 0;
	open_file(path, &fd);
	i = get_next_line(fd, &line);
	if (i < 0)
		ft_err("Not a valid file");
	while (i > 0)
	{
		parse_string(map, line, &status);
		free(line);
		i = get_next_line(fd, &line);
	}
	parse_string(map, line, &status);
	free(line);
	if ((status & START) != START)
		ft_err("File empty or not valid");
	return (1);
}
