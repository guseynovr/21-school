#include "fractol.h"

void	mandelbrot_zoom(int button, int x, int y, t_settings *sets)
{
	double	k;

	k = (sets->x_max - sets->x_min) * 0.2;
	if (button == 4 || button == 2)
	{
		sets->x_min -= k * (x / (double) sets->width);
		sets->x_max += k * (1 - x / (double) sets->width);
		sets->y_min -= k * (y / (double) sets->height);
		sets->y_max += k * (1 - y / (double) sets->height);
	}
	else if (button == 5 || button == 1)
	{
		sets->x_min += k * (x / (double) sets->width);
		sets->x_max -= k * (1 - x / (double) sets->width);
		sets->y_min += k * (y / (double) sets->height);
		sets->y_max -= k * (1 - y / (double) sets->height);
	}
	mlx_clear_window(sets->mlx, sets->win);
	sets->sc = 1;
	draw(sets);
	sets->sc = 0;
}

int	mouse_hook(int button, int x, int y, t_settings *sets)
{
	if (sets->set_id)
		julia_zoom(button, x, y, sets);
	else
		mandelbrot_zoom(button, x, y, sets);
	return (1);
}

void	mandelbrot_move(int keycode, t_settings *sets)
{
	double	k;

	k = (sets->x_max - sets->x_min) * 0.1;
	if (keycode == 123)
	{
		sets->x_min -= k;
		sets->x_max -= k;
	}
	else if (keycode == 124)
	{
		sets->x_min += k;
		sets->x_max += k;
	}
	else if (keycode == 125)
	{
		sets->y_min += k;
		sets->y_max += k;
	}
	else if (keycode == 126)
	{
		sets->y_min -= k;
		sets->y_max -= k;
	}
}

void	move(int keycode, t_settings *sets)
{
	if (sets->set_id)
		julia_move(keycode, sets);
	else
		mandelbrot_move(keycode, sets);
}
