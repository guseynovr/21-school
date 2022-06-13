#include "fractol.h"

int	get_color(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

char	*put_pixel(int color, char *addr)
{
	char	*a;

	a = addr;
	*a++ = color & 0xFF;
	*a++ = (color & 0xFF00) >> 8;
	*a++ = (color & 0xFF0000) >> 16;
	*a++ = 0;
	return (a);
}

void	set_pixel_color(t_settings *sets, int iter, int *colors)
{
	if (iter == sets->max_iter)
		sets->img_data = put_pixel(0x0, sets->img_data);
	else
	{
		if (iter / sets->color % 2 == 0)
			sets->img_data = put_pixel(colors[iter % sets->color],
					sets->img_data);
		else
			sets->img_data = put_pixel(
					colors[sets->color - (iter % sets->color) - 1],
					sets->img_data);
	}
}

void	draw(t_settings *sets)
{
	t_complex	c;
	int			colors[22];

	mlx_destroy_image(sets->mlx, sets->img);
	set_img(sets);
	init_palette(colors, sets->color);
	if (sets->set_id)
		draw_julia(sets, &c, colors);
	else
		draw_mandelbrot(sets, &c, colors);
	mlx_put_image_to_window(sets->mlx, sets->win, sets->img, 0, 0);
}
