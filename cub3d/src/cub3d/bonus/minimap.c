/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:18:14 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 16:21:03 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "math.h"

void	draw_tile(unsigned int *start, int mini_tile, int line,
unsigned int color)
{
	int				x;
	int				y;
	unsigned int	*origin;

	y = -1;
	while (++y < mini_tile)
	{
		x = -1;
		origin = start;
		while (++x < mini_tile)
			*start++ = color;
		start = origin + line;
	}
}

void	draw_mmap(t_map3d *map3d, t_map *map, unsigned int *start,
int mini_tile)
{
	const int		next_line = map3d->img->size[0] - map->size[0] * mini_tile
			+ map3d->img->size[0] * (mini_tile - 1);
	int				x;
	int				y;

	y = -1;
	while (++y < map->size[1])
	{
		x = -1;
		while (++x < map->size[0])
		{
			if (map->map[y][x] == '1')
				draw_tile(start, mini_tile, map3d->img->size[0], 0xFFFFFF);
			if (x == map3d->player[0] / map3d->tile_size
				&& y == map3d->player[1] / map3d->tile_size)
				draw_tile(start, mini_tile, map3d->img->size[0], 0x0);
			start += mini_tile;
		}
		start += next_line;
	}
}

void	draw_minimap(t_cub *cub)
{
	unsigned int	*start;
	int				mini_tile;
	int				player_icon_radius;

	mini_tile = pow(2, cub->map3d->log - 5);
	if (mini_tile < 10)
		mini_tile = 10;
	start = cub->map3d->img->pixels + cub->map3d->img->capacity + mini_tile
		- (cub->map3d->img->size[0] * (cub->map->size[1] + 1) * mini_tile);
	player_icon_radius = mini_tile / 3;
	draw_mmap(cub->map3d, cub->map, start, mini_tile);
}
