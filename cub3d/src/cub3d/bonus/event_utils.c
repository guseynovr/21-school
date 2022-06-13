/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:49:00 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 16:19:56 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "events.h"
#include "utils.h"
#include "cast.h"
#include <math.h>
#include "settings.h"

int	calc_angle(t_cub *cub, int flags)
{
	int	angle;

	if ((flags & M_LEFT) == M_LEFT && (flags & M_FORWARD) == M_FORWARD)
		angle = cub->map->player_dir + cub->angles->a45;
	else if ((flags & M_LEFT) == M_LEFT && (flags & M_BACKWARD) == M_BACKWARD)
		angle = cub->map->player_dir + cub->angles->a90 + cub->angles->a45;
	else if ((flags & M_LEFT) == M_LEFT)
		angle = cub->map->player_dir + cub->angles->a90;
	else if ((flags & M_RIGHT) == M_RIGHT && (flags & M_FORWARD) == M_FORWARD)
		angle = cub->map->player_dir - cub->angles->a45;
	else if ((flags & M_RIGHT) == M_RIGHT && (flags & M_BACKWARD) == M_BACKWARD)
		angle = cub->map->player_dir + cub->angles->a180 + cub->angles->a45;
	else if ((flags & M_RIGHT) == M_RIGHT)
		angle = cub->map->player_dir - cub->angles->a90;
	else if ((flags & M_BACKWARD) == M_BACKWARD)
		angle = cub->map->player_dir + cub->angles->a180;
	else if ((flags & M_FORWARD) == M_FORWARD)
		angle = cub->map->player_dir;
	else
		return (-1);
	angle = (cub->angles->a360 + angle) % cub->angles->a360;
	return (angle);
}

void	try_move(t_cub *cub, int angle, int wall_dist, const int *player_old)
{
	if (is_facing_left_idx(angle, cub->angles))
		cub->map3d->player[0] -= cub->r_data->values->m_stepX[angle];
	else
		cub->map3d->player[0] += cub->r_data->values->m_stepX[angle];
	if (is_facing_left_idx(angle, cub->angles)
		&& is_wall(cub, cub->map3d->player[0] - wall_dist,
			cub->map3d->player[1], angle))
		cub->map3d->player[0] = player_old[0];
	else if (is_wall(cub, cub->map3d->player[0] + wall_dist,
			cub->map3d->player[1], angle))
		cub->map3d->player[0] = player_old[0];
	if (is_facing_up_idx(angle, cub->angles))
		cub->map3d->player[1] -= cub->r_data->values->m_stepY[angle];
	else
		cub->map3d->player[1] += cub->r_data->values->m_stepY[angle];
	if (is_facing_up_idx(angle, cub->angles)
		&& is_wall(cub, cub->map3d->player[0],
			cub->map3d->player[1] - wall_dist, angle))
		cub->map3d->player[1] = player_old[1];
	else if (is_wall(cub, cub->map3d->player[0],
			cub->map3d->player[1] + wall_dist, angle))
		cub->map3d->player[1] = player_old[1];
}

void	movement_event(t_cub *cub)
{
	int			angle;
	int			flags;
	const int	player_old[2] = {cub->map3d->player[0], cub->map3d->player[1]};
	const int	wall_dist = pow(2, cub->map3d->log - 3);

	flags = cub->mov_flags;
	if ((flags & M_LEFT) == M_LEFT && (flags & M_RIGHT) == M_RIGHT)
		flags = (flags ^ M_LEFT) & (flags ^ M_RIGHT);
	if ((flags & M_FORWARD) == M_FORWARD && (flags & M_BACKWARD) == M_BACKWARD)
		flags = (flags ^ M_FORWARD) & (flags ^ M_BACKWARD);
	angle = calc_angle(cub, flags);
	if (angle == -1)
		return ;
	try_move(cub, angle, wall_dist, player_old);
}

void	turn_event(t_cub *cub)
{
	const int	step = TURN_SPEED * (cub->angles->a5 / 10);

	if ((cub->turn_flags & T_LEFT) == T_LEFT
		&& (cub->turn_flags & T_RIGHT) == T_RIGHT)
		return ;
	if ((cub->turn_flags & T_LEFT) == T_LEFT)
		cub->map->player_dir = (cub->map->player_dir + step)
			% cub->angles->a360;
	else if ((cub->turn_flags & T_RIGHT) == T_RIGHT)
	{
		cub->map->player_dir -= step;
		if (cub->map->player_dir < 0)
			cub->map->player_dir = cub->angles->a360
				+ cub->map->player_dir;
	}
}
