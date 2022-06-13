/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:53:10 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/03 19:47:34 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "math.h"
#include "draw.h"
#include "draw_utils.h"

void	draw_wall(t_cub *cub, t_slice *slice)
{
	int			i;
	t_image		*map_img;
	t_draw_vars	vars;

	init_vars(&vars, cub, slice);
	i = slice->top;
	map_img = cub->map3d->img;
	while (i < slice->bottom)
	{
		map_img->pixels[i] = vars.xpm_pixels[vars.xpm_place];
		vars.total += vars.step;
		if (vars.total >= 1.)
		{
			vars.xpm_place += vars.xpm_size * (int)vars.total;
			vars.total -= (int)vars.total;
		}
		i += map_img->size[0];
	}
}

void	draw_ceiling(t_cub *cub, t_slice *slice)
{
	int		i;
	t_image	*map_img;

	map_img = cub->map3d->img;
	i = slice->x;
	while (i < slice->top)
	{
		map_img->pixels[i] = cub->map->resources.ceiling;
		i += map_img->size[0];
	}
}

void	draw_floor(t_cub *cub, t_slice *slice)
{
	int		i;
	t_image	*map_img;

	map_img = cub->map3d->img;
	i = slice->bottom;
	while (i < map_img->capacity)
	{
		map_img->pixels[i] = cub->map->resources.floor;
		i += map_img->size[0];
	}
}

void	draw_slice(t_image *map_img, t_slice *slice, t_cub *cub)
{
	if (slice->len >= map_img->size[1])
	{
		slice->top = slice->x;
		slice->bottom = slice->x + map_img->capacity - map_img->size[0];
		slice->y = (slice->len - map_img->size[1]) >> 1;
	}
	else
	{
		slice->top = ((map_img->size[1] - slice->len) >> 1) * map_img->size[0]
			+ slice->x;
		slice->bottom = ((map_img->size[1] + slice->len) >> 1)
			* map_img->size[0] + slice->x;
		slice->y = 0;
	}
	draw_wall(cub, slice);
	draw_floor(cub, slice);
	draw_ceiling(cub, slice);
}

void	draw(t_cub *cub)
{
	int		i;
	float	ray_len;
	t_slice	slice;

	i = -1;
	while (++i < cub->win_size[0])
	{
		ray_len = cub->r_data->rays[i].len;
		slice.len = round(cub->map3d->tile_size / ray_len
				* cub->r_data->dist_to_scrn);
		slice.x = i;
		draw_slice(cub->map3d->img, &slice, cub);
	}
	draw_minimap(cub);
}
