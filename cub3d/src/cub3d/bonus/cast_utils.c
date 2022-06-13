/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:36:16 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/03 19:32:23 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "utils.h"
#include <math.h>

int	is_wall(t_cub *cub, float x, float y, float angle)
{
	int		x_map;
	int		y_map;
	t_map	*map;

	map = cub->map;
	if (is_facing_left_idx(angle, cub->angles))
		x_map = (int)ceil(x) >> cub->map3d->log;
	else
		x_map = (int)floor(x) >> cub->map3d->log;
	if (is_facing_up_idx(angle, cub->angles))
		y_map = (int)ceil(y) >> cub->map3d->log;
	else
		y_map = (int)floor(y) >> cub->map3d->log;
	if (x_map < 0 || x_map >= map->size[0]
		|| y_map < 0 || y_map >= map->size[1])
		return (-1);
	if (map->map[y_map][x_map] == '1')
		return (1);
	return (0);
}

int	find_first_horizontal(t_cub *cub, int angle, float *fp)
{
	int		opposite;
	int		*player;
	int		log;

	player = cub->map3d->player;
	log = cub->map3d->log;
	if (angle == 0 || angle == cub->angles->a180)
		return (-1);
	if (is_facing_up_idx(angle, cub->angles))
		fp[1] = ((player[1] >> log) << log) - 1;
	else
		fp[1] = ((player[1] >> log) << log) + cub->map3d->tile_size;
	opposite = player[1] - fp[1];
	if (is_facing_left_idx(angle, cub->angles))
		fp[0] = player[0] - mabs(opposite * cub->r_data->values->itan[angle]);
	else
		fp[0] = player[0] + mabs(opposite * cub->r_data->values->itan[angle]);
	return (0);
}

int	find_first_vertical(t_cub *cub, int angle, float *fp)
{
	int		adjacent;
	int		*player;
	int		log;

	player = cub->map3d->player;
	log = cub->map3d->log;
	if (angle == cub->angles->a90 || angle == cub->angles->a270)
		return (-1);
	if (is_facing_left_idx(angle, cub->angles))
		fp[0] = ((player[0] >> log) << log) - 1;
	else
		fp[0] = ((player[0] >> log) << log) + cub->map3d->tile_size;
	adjacent = player[0] - fp[0];
	if (is_facing_up_idx(angle, cub->angles))
		fp[1] = player[1] - mabs(adjacent * cub->r_data->values->tan[angle]);
	else
		fp[1] = player[1] + mabs(adjacent * cub->r_data->values->tan[angle]);
	return (0);
}
