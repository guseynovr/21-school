/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:53:23 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/03 14:08:08 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "math.h"
#include "render.h"
#include <stdlib.h>
#include "utils.h"

float	to_radians(float degree)
{
	return (degree * (M_PI / 180));
}

t_image	*new_image(void *mlx, int *win_size, char *xpm)
{
	t_image	*image;

	image = malloc(sizeof(t_image));
	if (!image)
		ft_err("malloc failed\n");
	if (xpm)
		image->img = mlx_xpm_file_to_image(mlx, xpm, &image->size[0],
				&image->size[1]);
	else
		image->img = mlx_new_image(mlx, win_size[0], win_size[1]);
	if (!image->img)
		ft_err("mlx_new_image failed\n");
	image->pixels = (unsigned int *)mlx_get_data_addr(image->img,
			&image->bits_per_pixel, &image->size_line, &image->is_big_endian);
	if (!xpm)
	{
		image->size[0] = win_size[0];
		image->size[1] = win_size[1];
	}
	image->capacity = image->size[0] * image->size[1];
	return (image);
}

t_image	**init_textures(void *mlx, t_resources *resources)
{
	t_image	**textures;

	textures = malloc(sizeof(t_image *) * 4);
	if (!textures)
		ft_err("malloc failed\n");
	textures[NORTH] = new_image(mlx, 0, resources->north);
	textures[SOUTH] = new_image(mlx, 0, resources->south);
	textures[WEST] = new_image(mlx, 0, resources->west);
	textures[EAST] = new_image(mlx, 0, resources->east);
	return (textures);
}

void	init_player_dir(int *player_dir, t_angle *angle)
{
	if (*player_dir == 90)
		*player_dir = angle->a90;
	else if (*player_dir == 180)
		*player_dir = angle->a180;
	else if (*player_dir == 270)
		*player_dir = angle->a270;
	else
		*player_dir = 0;
}
