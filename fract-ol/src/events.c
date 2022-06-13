#include "fractol.h"

void	change_depth(int keycode, t_settings *sets)
{
	if (keycode == 27 && sets->max_iter > 1 && sets->max_iter < 51)
		sets->max_iter -= 1;
	else if (keycode == 27 && sets->max_iter > 1)
		sets->max_iter /= 1.1;
	else if (keycode == 24 && sets->max_iter < 50)
		sets->max_iter += 1;
	else if (keycode == 24 || sets->max_iter < 600)
		sets->max_iter *= 1.1;
}

void	change_color(t_settings *sets)
{
	if (sets->color < 22)
		sets->color += 3;
	else
		sets->color = BROWN;
}

int	key_hook(int keycode, t_settings *sets)
{
	if ((keycode >= 123 && keycode <= 126))
		move(keycode, sets);
	else if ((keycode >= 0 && keycode <= 2) || keycode == 13)
		julia_hook(keycode, sets);
	else if (keycode == 24 || keycode == 27)
		change_depth(keycode, sets);
	else if (keycode == 15)
		reset(sets);
	else if (keycode == 8)
		change_color(sets);
	else if (keycode == 53)
		destroy(sets);
	else if (keycode == 49 && sets->set_id)
		switch_animate(sets);
	else if (keycode == 43 && sets->set_id)
		sets->speed -= 0.01;
	else if (keycode == 47 && sets->set_id)
		sets->speed += 0.01;
	draw(sets);
	return (1);
}
