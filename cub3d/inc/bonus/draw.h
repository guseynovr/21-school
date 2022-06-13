/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:47:58 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/03 19:39:04 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

typedef struct s_slice
{
	int	top;
	int	bottom;
	int	x;
	int	y;
	int	len;
}	t_slice;

typedef struct s_draw_vars
{
	unsigned int	*xpm_pixels;
	int				xpm_size;
	int				xpm_place;
	float			step;
	float			total;
}	t_draw_vars;

#endif
