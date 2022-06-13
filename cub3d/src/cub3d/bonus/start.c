/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:01:42 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 16:31:53 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "events.h"
#include "cast.h"
#include "mlx.h"

void	start(t_map *map)
{
	t_cub	cub;

	init_cub(&cub, map);
	cast_rays(&cub);
	draw(&cub);
	mlx_hook(cub.window, 02, (1L << 0), key_pressed, &cub);
	mlx_hook(cub.window, 03, (1L << 1), key_released, &cub);
	mlx_hook(cub.window, 17, (1L << 17), destroy, &cub);
	mlx_loop_hook(cub.mlx, loop_hook, &cub);
	mlx_hook(cub.window, 06, (1L << 6), mouse_hook, &cub);
	mlx_mouse_hide();
	mlx_loop(cub.mlx);
}
