/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 12:46:58 by aarson            #+#    #+#             */
/*   Updated: 2021/11/04 18:13:36 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "parse.h"

void	valid_str_map(t_map *map, char *line, int *status)
{
	char	**tmp;
	int		i;

	if ((*status & START) != START)
		*status = *status | START;
	if (!*line)
		ft_err("Parse error: Empty line inner map");
	tmp = malloc(sizeof(char *) * (map->player_dir + 2));
	if (!tmp)
		ft_err("Malloc\n");
	i = -1;
	while (++i < map->player_dir)
		tmp[i] = map->map[i];
	tmp[i++] = ft_strdup(line);
	tmp[i] = 0;
	map->player_dir += 1;
	free(map->map);
	map->map = tmp;
}

void	get_player_pos(t_map *map, int x, int y, char dir)
{
	map->player[0] = x;
	map->player[1] = y;
	if (dir == 'N')
		map->player_dir = 90;
	else if (dir == 'S')
		map->player_dir = 270;
	else if (dir == 'W')
		map->player_dir = 180;
	else
		map->player_dir = 0;
}

int	valid_map(t_map *map)
{
	check_unnecesary_sym(map->map);
	check_outer_borders(map->map);
	check_player_availability(map);
	check_zeroes(map->map);
	return (1);
}

char	**get_arr_place(t_map *map, int max)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * (len_arr(map->map) + 1));
	if (!new)
		ft_err("Malloc");
	i = -1;
	while (map->map[++i])
	{
		new[i] = ft_calloc(1, (max + 1));
		if (!new[i])
			ft_err("Malloc");
	}
	return (new);
}

int	fill_to_rectangle(t_map *map)
{
	int		max;
	int		i;
	char	**new;

	max = find_max_str(map->map);
	new = get_arr_place(map, max);
	i = -1;
	while (map->map[++i])
	{
		ft_memcpy(new[i], map->map[i], ft_strlen(map->map[i]));
		ft_memset(&(new[i][ft_strlen(map->map[i])]), '0',
			max - ft_strlen(map->map[i]));
	}
	new[i] = 0;
	free_arr(map->map);
	map->map = new;
	map->size[0] = max;
	map->size[1] = i;
	return (1);
}
