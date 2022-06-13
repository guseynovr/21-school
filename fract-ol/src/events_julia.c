#include "fractol.h"

void	julia_hook(int keycode, t_settings *sets)
{
	double	k;

	if (!sets->set_id)
		return ;
	k = 0.01;
	if (keycode == 0 && sets->c_x > -2.0)
		sets->c_x -= k;
	else if (keycode == 2 && sets->c_x < 2.0)
		sets->c_x += k;
	else if (keycode == 1 && sets->c_y > -2.0)
		sets->c_y -= k;
	else if (keycode == 13 && sets->c_y < 2.0)
		sets->c_y += k;
	draw(sets);
}

int	julia_loop(t_settings *sets)
{
	static double	a = 0.1;

	if (!sets->set_id || !sets->animate)
		return (0);
	if (a >= 360)
		a = 0.0;
	else
		a += sets->speed;
	sets->c_x = 0.7885 * cos(a);
	sets->c_y = 0.7885 * sin(a);
	draw(sets);
	return (1);
}

void	switch_animate(t_settings *sets)
{
	sets->animate = !sets->animate;
}

void	julia_zoom(int button, int x, int y, t_settings *sets)
{
	double	k;

	(void) x;
	(void) y;
	k = 1.1;
	if (button == 4 || button == 2)
		sets->j_size *= k;
	else if (button == 5 || button == 1)
		sets->j_size /= k;
	mlx_clear_window(sets->mlx, sets->win);
	draw(sets);
}

void	julia_move(int keycode, t_settings *sets)
{
	double	k;

	k = 0.1;
	if (keycode == 123)
		sets->j_x_pl -= k;
	else if (keycode == 124)
		sets->j_x_pl += k;
	else if (keycode == 125)
		sets->j_y_pl += k;
	else if (keycode == 126)
		sets->j_y_pl -= k;
}
