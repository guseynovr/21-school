/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:18:22 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/03 19:30:38 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "math.h"

int	is_facing_up_idx(int angle, t_angle *a)
{
	return (angle > 0 && angle < a->a180);
}

int	is_facing_left_idx(int angle, t_angle *a)
{
	return (angle > a->a90 && angle < a->a270);
}

int	is_facing_up_radians(float angle)
{
	return (angle > 0 && angle < M_PI);
}

int	is_facing_left_radians(float angle)
{
	return (angle > M_PI_2 && angle < M_PI + M_PI_2);
}

float	mabs(float n)
{
	if (n < 0)
		return (-n);
	return (n);
}
