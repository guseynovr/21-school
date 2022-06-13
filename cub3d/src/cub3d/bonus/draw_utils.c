/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:43:50 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/03 19:48:10 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "math.h"
#include "draw.h"

void	init_vars(t_draw_vars *vars, t_cub *cub, t_slice *slice)
{
	t_ray	*ray;
	int		tile_size;
	int		xpm_x;
	float	xpm_y;

	ray = &cub->r_data->rays[slice->x];
	tile_size = cub->map3d->tile_size;
	vars->xpm_size = cub->textures[ray->t_idx]->size[0];
	vars->step = (float)vars->xpm_size / slice->len;
	xpm_x = (int)floor((float)vars->xpm_size * ray->offset / tile_size);
	xpm_y = (int)floor(vars->step * slice->y);
	vars->xpm_place = xpm_y * vars->xpm_size + xpm_x;
	vars->total = vars->step * slice->y - floor(vars->step * slice->y);
	vars->xpm_pixels = cub->textures[ray->t_idx]->pixels;
}
