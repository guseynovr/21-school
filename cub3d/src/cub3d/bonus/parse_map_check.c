/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:25:20 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 16:25:26 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "parse.h"
#include <stdio.h>

void	check_zeroes(char **map)
{
	int	i;
	int	k;

	i = -1;
	while (map[++i])
	{
		k = -1;
		while (map[i][++k])
		{
			if (map[i][k] == '0')
				check_correct_pos(map, k, i);
		}
	}
}

void	check_player_availability(t_map *map)
{
	int		x;
	int		y;
	char	*player_type;

	player_type = ft_strdup("WESN");
	if (!player_type)
		ft_err("Malloc error");
	y = -1;
	while (map->map[++y])
	{
		x = -1;
		while (map->map[y][++x])
		{
			if (ft_strchr(player_type, map->map[y][x]))
			{
				check_correct_pos(map->map, x, y);
				get_player_pos(map, x, y, map->map[y][x]);
				free(player_type);
				return ;
			}
		}
	}
	free(player_type);
	ft_err("No player in map");
}

void	check_outer_borders(char **map)
{
	int	i;
	int	k;

	i = -1;
	while (map[0][++i])
		if (map[0][i] != '1' && map[0][i] != ' ')
			ft_err("Invalid map");
	k = len_arr(map) - 1;
	i = -1;
	while (map[k][++i])
		if (map[k][i] != '1' && map[k][i] != ' ')
			ft_err("Invalid map");
	i = -1;
	while (map[++i])
		if (map[i][0] != '1' && map[i][0] != ' ')
			ft_err("Invalid map");
	i = -1;
	while (map[++i])
		if ((map[i][ft_strlen(map[i]) - 1] != '1')
		&& (map[i][ft_strlen(map[i]) - 1] != ' '))
			ft_err("Invalid map");
}

void	check_unnecesary_sym(char **map)
{
	char	*sym;
	int		i;
	int		k;

	sym = ft_strdup("01 WESN");
	if (!sym)
		ft_err("Malloc error");
	i = -1;
	while (map[++i])
	{
		k = -1;
		while (map[i][++k])
			if (!(ft_strchr(sym, map[i][k])))
				ft_err("Incorrect type symbol in map");
	}
	free(sym);
}

void	check_correct_pos(char **map, int x, int y)
{
	int	prev_len;
	int	next_len;
	int	pos;

	pos = ft_strlen(map[y]) - (ft_strlen(map[y]) - x);
	prev_len = ft_strlen(map[y - 1]);
	next_len = ft_strlen(map[y + 1]);
	if (pos >= prev_len || pos >= next_len)
		ft_err("Map not closed");
	if (map[y - 1][x - 1] == ' ' || map[y - 1][x] == ' ' || map[y - 1][x + 1]
	 == ' ' || map[y][x - 1] == ' ' || map[y][x + 1] == ' ' || map[y + 1]
	[x - 1] == ' ' || map[y + 1][x] == ' ' || map[y + 1][x + 1] == ' ')
		ft_err("Map not closed");
	if (map[y - 1][x - 1] == '\0' || map[y - 1][x] == '\0' || map[y - 1][x + 1]
	 == '\0' || map[y][x - 1] == '\0' || map[y][x + 1] == '\0' || map[y + 1]
	[x - 1] == '\0' || map[y + 1][x] == '\0' || map[y + 1][x + 1] == '\0')
		ft_err("Map not closed");
}
