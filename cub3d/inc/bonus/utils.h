/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:30:02 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 16:31:15 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "render.h"

int		is_facing_up_idx(int angle, t_angle *a);
int		is_facing_left_idx(int angle, t_angle *a);
int		is_facing_up_radians(float angle);
int		is_facing_left_radians(float angle);
float	mabs(float n);

#endif
