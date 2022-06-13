/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:52:49 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 16:28:58 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_UTILS_H
# define INIT_UTILS_H

# include "render.h"

float	to_radians(float degree);
t_image	*new_image(void *mlx, int *win_size, char *xpm);
t_image	**init_textures(void *mlx, t_resources *resources);
void	init_player_dir(int *player_dir, t_angle *angle);

#endif
