/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:01:45 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/03 20:26:21 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "math.h"
#include "utils.h"
#include "render.h"
#include <stdlib.h>
#include "settings.h"
#include "init_utils.h"
#include "init_r_data.h"

void	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		ft_err("mlx_init failed\n");
	cub->win_size[0] = DEFAULT_WIDTH;
	cub->win_size[1] = DEFAULT_HEIGHT;
	if (DEFAULT_WIDTH < MIN_WIDTH)
		cub->win_size[0] = MIN_WIDTH;
	else if (DEFAULT_WIDTH > MAX_WIDTH)
		cub->win_size[0] = MAX_WIDTH;
	if (DEFAULT_HEIGHT < MIN_HEIGHT)
		cub->win_size[1] = MIN_HEIGHT;
	else if (DEFAULT_HEIGHT > MAX_HEIGHT)
		cub->win_size[1] = MAX_HEIGHT;
	cub->window = mlx_new_window(cub->mlx, cub->win_size[0], cub->win_size[1],
			NAME);
	if (!cub->window)
		ft_err("mlx_new_window failed\n");
}

t_map3d	*new_map3d(void *mlx, int *win_size, int raw_player[2])
{
	t_map3d	*map3d;

	map3d = malloc(sizeof(t_map3d));
	if (!map3d)
		ft_err("mlx_init failed\n");
	map3d->img = new_image(mlx, win_size, 0);
	map3d->log = (int)round(log2(win_size[0])) - 2;
	map3d->tile_size = 1 << map3d->log;
	map3d->player[0] = raw_player[0] * map3d->tile_size
		+ (map3d->tile_size >> 1);
	map3d->player[1] = raw_player[1] * map3d->tile_size
		+ (map3d->tile_size >> 1);
	return (map3d);
}

void	init_cub(t_cub *cub, t_map *map)
{
	cub->map = map;
	init_mlx(cub);
	cub->map3d = new_map3d(cub->mlx, cub->win_size, cub->map->player);
	cub->r_data = new_r_data(cub);
	cub->mov_flags = 0;
	cub->turn_flags = 0;
	cub->textures = init_textures(cub->mlx, &cub->map->resources);
	cub->angles = init_angles(cub->win_size[0]);
	init_player_dir(&cub->map->player_dir, cub->angles);
}
