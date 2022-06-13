/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:53:03 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/03 13:38:33 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "math.h"
#include "utils.h"
#include "cast.h"

float	cast_horizontal(t_cub *cub, int angle, float *next_point)
{
	float	xA;
	float	yA;
	int		wall_check;

	if (find_first_horizontal(cub, angle, next_point) == -1)
		return (INFINITY);
	if (is_facing_up_idx(angle, cub->angles))
		yA = -cub->map3d->tile_size;
	else
		yA = cub->map3d->tile_size;
	xA = cub->r_data->values->xA[angle];
	wall_check = is_wall(cub, next_point[0], next_point[1], angle);
	while (wall_check == 0)
	{
		next_point[0] += xA;
		next_point[1] += yA;
		wall_check = is_wall(cub, next_point[0], next_point[1], angle);
	}
	if (wall_check == -1)
		return (INFINITY);
	return (mabs((cub->map3d->player[1] - next_point[1])
			* cub->r_data->values->isin[angle]));
}

float	cast_vertical(t_cub *cub, int angle, float *next_point)
{
	float	xA;
	float	yA;
	int		wall_check;

	if (find_first_vertical(cub, angle, next_point) == -1)
		return (INFINITY);
	if (is_facing_left_idx(angle, cub->angles))
		xA = -cub->map3d->tile_size;
	else
		xA = cub->map3d->tile_size;
	yA = cub->r_data->values->yA[angle];
	wall_check = is_wall(cub, next_point[0], next_point[1], angle);
	while (wall_check == 0)
	{
		next_point[0] += xA;
		next_point[1] += yA;
		wall_check = is_wall(cub, next_point[0], next_point[1], angle);
	}
	if (wall_check == -1)
		return (INFINITY);
	return (mabs((cub->map3d->player[0] - next_point[0])
			* cub->r_data->values->icos[angle]));
}

int	get_texture_id(int horizontal, int angle, t_angle *a)
{
	if (horizontal && is_facing_up_idx(angle, a))
		return (NORTH);
	else if (horizontal)
		return (SOUTH);
	else if (!horizontal && is_facing_left_idx(angle, a))
		return (WEST);
	else
		return (EAST);
}

void	render_ray(t_cub *cub, int angle, t_ray *ray)
{
	float	h_dist;
	float	v_dist;
	float	h_point[2];
	float	v_point[2];
	int		relative_angle;

	relative_angle = (int)mabs(angle - cub->map->player_dir);
	h_dist = cast_horizontal(cub, angle, h_point);
	v_dist = cast_vertical(cub, angle, v_point);
	if (h_dist < v_dist)
	{
		ray->len = h_dist * cub->r_data->values->fish[relative_angle];
		ray->offset = (int)round(h_point[0]) % cub->map3d->tile_size;
		ray->t_idx = get_texture_id(1, angle, cub->angles);
	}
	else
	{
		ray->len = v_dist * cub->r_data->values->fish[relative_angle];
		ray->offset = (int)round(v_point[1]) % cub->map3d->tile_size;
		ray->t_idx = get_texture_id(0, angle, cub->angles);
	}
}

void	cast_rays(t_cub *cub)
{
	int	angle;
	int	i;

	i = -1;
	angle = cub->map->player_dir + cub->angles->a30;
	if (angle > cub->angles->a360)
		angle = angle % cub->angles->a360;
	while (++i < cub->r_data->count)
	{
		render_ray(cub, angle, &cub->r_data->rays[i]);
		angle--;
		if (angle < 0)
			angle = cub->angles->a360 + angle;
	}
}
