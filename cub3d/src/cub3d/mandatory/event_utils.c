/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:49:00 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/03 14:15:06 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "events.h"
#include "utils.h"

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

void	movement_event(t_cub *cub)
{
	int			angle;
	int			flags;

	flags = cub->mov_flags;
	if ((flags & M_LEFT) == M_LEFT && (flags & M_RIGHT) == M_RIGHT)
		flags = (flags ^ M_LEFT) & (flags ^ M_RIGHT);
	if ((flags & M_FORWARD) == M_FORWARD && (flags & M_BACKWARD) == M_BACKWARD)
		flags = (flags ^ M_FORWARD) & (flags ^ M_BACKWARD);
	angle = calc_angle(cub, flags);
	if (angle == -1)
		return ;
	if (is_facing_left_idx(angle, cub->angles))
		cub->map3d->player[0] -= cub->r_data->values->m_stepX[angle];
	else
		cub->map3d->player[0] += cub->r_data->values->m_stepX[angle];
	if (is_facing_up_idx(angle, cub->angles))
		cub->map3d->player[1] -= cub->r_data->values->m_stepY[angle];
	else
		cub->map3d->player[1] += cub->r_data->values->m_stepY[angle];
}
