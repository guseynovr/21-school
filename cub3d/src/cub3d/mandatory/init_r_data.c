/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_r_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:00:58 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/03 20:30:34 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "mlx.h"
#include "math.h"
#include "settings.h"
#include "utils.h"
#include "init_utils.h"
#include <stdlib.h>

t_angle	*init_angles(int width)
{
	t_angle	*angles;

	angles = malloc(sizeof(t_angle));
	if (!angles)
		ft_err("malloc failed\n");
	angles->a60 = width;
	angles->a30 = angles->a60 / 2;
	angles->a360 = angles->a60 * 6;
	angles->a90 = angles->a30 * 3;
	angles->a180 = angles->a60 * 3;
	angles->a270 = angles->a90 * 3;
	angles->a15 = angles->a30 / 2;
	angles->a45 = angles->a15 * 3;
	angles->a5 = angles->a30 / 6;
	return (angles);
}

void	init_steps(t_values *vals, int i, float a, int tile_size)
{
	if (is_facing_left_radians(a))
		vals->xA[i] = -mabs(tile_size * vals->itan[i]);
	else
		vals->xA[i] = mabs(tile_size * vals->itan[i]);
	if (is_facing_up_radians(a))
		vals->yA[i] = -mabs(tile_size * vals->tan[i]);
	else
		vals->yA[i] = mabs(tile_size * vals->tan[i]);
}

void	fill_values(t_values *vals, int cnt, double angle, t_cub *cub)
{
	int		i;
	float	a;
	int		step;

	step = MOVE_SPEED * pow(2, cub->map3d->log - 4);
	i = -1;
	a = 0;
	while (++i < cnt)
	{
		vals->sin[i] = sin(a);
		vals->cos[i] = cos(a);
		vals->isin[i] = 1 / sin(a);
		vals->icos[i] = 1 / cos(a);
		vals->tan[i] = tan(a);
		vals->itan[i] = 1 / tan(a);
		vals->fish[i] = mabs(vals->cos[i]);
		init_steps(vals, i, a, cub->map3d->tile_size);
		vals->m_stepX[i] = (int)mabs(round(16 * MOVE_SPEED * vals->cos[i]));
		vals->m_stepY[i] = (int)mabs(round(16 * MOVE_SPEED * vals->sin[i]));
		a += angle;
	}
}

t_values	*init_values(int cnt, double angle, t_cub *cub)
{
	t_values	*vals;

	vals = malloc(sizeof(t_values));
	if (!vals)
		ft_err("malloc failed\n");
	vals->sin = malloc(sizeof(double) * cnt);
	vals->cos = malloc(sizeof(double) * cnt);
	vals->isin = malloc(sizeof(double) * cnt);
	vals->icos = malloc(sizeof(double) * cnt);
	vals->tan = malloc(sizeof(double) * cnt);
	vals->itan = malloc(sizeof(double) * cnt);
	vals->fish = malloc(sizeof(double) * cnt);
	vals->xA = malloc(sizeof(double) * cnt);
	vals->yA = malloc(sizeof(double) * cnt);
	vals->m_stepX = malloc(sizeof(int) * cnt);
	vals->m_stepY = malloc(sizeof(int) * cnt);
	if (!vals->sin || !vals->cos || !vals->isin || !vals->icos || !vals->tan
		|| !vals->itan || !vals->fish || !vals->xA || !vals->yA
		|| !vals->m_stepX || !vals->m_stepY)
		ft_err("malloc failed\n");
	fill_values(vals, cnt, to_radians(angle), cub);
	return (vals);
}

t_render	*new_r_data(t_cub *cub)
{
	t_render	*r_data;

	r_data = malloc(sizeof(t_render));
	if (!r_data)
		ft_err("malloc failed\n");
	r_data->count = cub->win_size[0];
	r_data->cnt360 = cub->win_size[0] * (360 / FOV);
	r_data->dist_to_scrn = (cub->win_size[0] >> 1) * 1.0
		/ tan(to_radians(FOV >> 1));
	r_data->angle = (FOV * 1.0) / cub->win_size[0];
	r_data->rays = malloc(sizeof(t_ray) * cub->win_size[0]);
	if (!r_data->rays)
		ft_err("malloc failed\n");
	r_data->values = init_values(cub->win_size[0] * (360 / FOV), r_data->angle,
			cub);
	return (r_data);
}
