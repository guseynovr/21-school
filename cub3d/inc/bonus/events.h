/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:48:22 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 15:37:13 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# define M_LEFT			0x1
# define M_RIGHT		0x2
# define M_FORWARD		0x4
# define M_BACKWARD		0x8

# define T_LEFT			0x1
# define T_RIGHT		0x2

# define R_OFFSET		10

enum	e_button
{
	A,
	S,
	D,
	W = 13,
	ARROW_LEFT = 123,
	ARROW_RIGHT = 124
};

int	destroy(t_cub *cub);
int	key_pressed(int keycode, t_cub *cub);
int	key_released(int keycode, t_cub *cub);
int	loop_hook(t_cub *cub);
int	mouse_hook(int x, int y, t_cub *cub);

#endif
