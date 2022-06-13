/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:54:24 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 16:31:39 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "events.h"
#include "settings.h"
#include "libft.h"
#include "utils.h"
#include "cast.h"
#include "event_utils.h"
#include "mlx.h"

int	destroy(t_cub *cub)
{
	mlx_destroy_window(cub->mlx, cub->window);
	mlx_destroy_image(cub->mlx, cub->map3d->img);
	mlx_destroy_image(cub->mlx, cub->textures[NORTH]);
	mlx_destroy_image(cub->mlx, cub->textures[SOUTH]);
	mlx_destroy_image(cub->mlx, cub->textures[WEST]);
	mlx_destroy_image(cub->mlx, cub->textures[EAST]);
	exit(0);
}

int	key_pressed(int keycode, t_cub *cub)
{
	if (keycode == ARROW_LEFT)
		cub->turn_flags = cub->turn_flags | T_LEFT;
	else if (keycode == ARROW_RIGHT)
		cub->turn_flags = cub->turn_flags | T_RIGHT;
	else if (keycode == A)
		cub->mov_flags = cub->mov_flags | M_LEFT;
	else if (keycode == D)
		cub->mov_flags = cub->mov_flags | M_RIGHT;
	else if (keycode == W)
		cub->mov_flags = cub->mov_flags | M_FORWARD;
	else if (keycode == S)
		cub->mov_flags = cub->mov_flags | M_BACKWARD;
	else if (keycode == 53)
		destroy(cub);
	return (0);
}

int	key_released(int keycode, t_cub *cub)
{
	if (keycode == ARROW_LEFT)
		cub->turn_flags = cub->turn_flags ^ T_LEFT;
	else if (keycode == ARROW_RIGHT)
		cub->turn_flags = cub->turn_flags ^ T_RIGHT;
	else if (keycode == A)
		cub->mov_flags = cub->mov_flags ^ M_LEFT;
	else if (keycode == D)
		cub->mov_flags = cub->mov_flags ^ M_RIGHT;
	else if (keycode == W)
		cub->mov_flags = cub->mov_flags ^ M_FORWARD;
	else if (keycode == S)
		cub->mov_flags = cub->mov_flags ^ M_BACKWARD;
	return (0);
}

int	mouse_hook(int x, int y, t_cub *cub)
{
	(void) y;
	if (cub->last_x > cub->win_size[0] - R_OFFSET)
	{
		cub->last_x = R_OFFSET;
		x = cub->last_x;
	}
	else if (cub->last_x && cub->last_x < R_OFFSET)
	{
		cub->last_x = cub->win_size[0] - R_OFFSET;
		x = cub->last_x;
	}
	if (x > 0 && cub->win_size[0] - x < R_OFFSET)
		mlx_mouse_move(cub->window, R_OFFSET, y);
	else if (x < R_OFFSET)
		mlx_mouse_move(cub->window, cub->win_size[0] - R_OFFSET, y);
	cub->map->player_dir += (cub->last_x - x) * TURN_SPEED;
	cub->map->player_dir = (cub->angles->a360 + cub->map->player_dir)
		% cub->angles->a360;
	cub->last_x = x;
	return (0);
}

int	loop_hook(t_cub *cub)
{
	if (cub->mov_flags)
		movement_event(cub);
	if (cub->turn_flags)
		turn_event(cub);
	ft_bzero(cub->map3d->img->pixels,
		sizeof(unsigned int) * cub->map3d->img->capacity);
	mlx_clear_window(cub->mlx, cub->window);
	cast_rays(cub);
	draw(cub);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->map3d->img->img, 0, 0);
	return (0);
}
