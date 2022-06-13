#include "fractol.h"

void	reset_c(t_settings *sets)
{
	if (sets->set_id)
	{
		sets->c_x = -0.4;
		sets->c_y = 0.6;
	}
	else
	{
		sets->c_x = (sets->x_max - sets->x_min) / (sets->width - 1);
		sets->c_y = (sets->y_max - sets->y_min) / (sets->height - 1);
	}
}

void	reset(t_settings *sets)
{
	sets->x_min = -2;
	sets->x_max = 2;
	sets->y_min = -2;
	sets->y_max = 2;
	reset_c(sets);
	sets->speed = 0.02;
	sets->max_iter = MAX_ITER;
	sets->animate = 0;
	sets->r = 2;
	sets->j_size = 2;
	sets->j_x_pl = 0;
	sets->j_y_pl = 0;
}

void	is_bounded(t_complex *c, t_settings *sets)
{
	c->c_re = sets->x_min + sets->c_x * c->col;
	c->x = c->c_re;
	c->y = c->c_im;
	c->x2 = pow(c->c_re, 2);
	c->y2 = pow(c->c_im, 2);
	if (sets->set_id)
	{
		c->c_re = -0.4;
		c->c_im = 0.6;
	}
	c->iter = 0;
	while (c->x2 + c->y2 <= 4 && c->iter < sets->max_iter)
	{
		c->y = 2 * c->x * c->y + c->c_im;
		c->x = c->x2 - c->y2 + c->c_re;
		c->x2 = pow(c->x, 2);
		c->y2 = pow(c->y, 2);
		c->iter++;
	}
}

void	draw_julia(t_settings *sets, t_complex *c, int *colors)
{
	c->row = -1;
	while (++c->row < HEIGHT)
	{
		c->col = -1;
		while (++c->col < WIDTH)
		{
			c->x = sets->j_size * sets->r * (c->col - sets->width / 2.0)
				/ sets->width;
			c->y = sets->j_size * sets->r * (c->row - sets->height / 2.0)
				/ sets->height;
			c->x += sets->j_x_pl * (sets->j_size / 2);
			c->y += sets->j_y_pl * (sets->j_size / 2);
			c->iter = 0;
			while (pow(c->x, 2.0) + pow(c->y, 2.0) < pow(sets->r, 2.0)
				&& c->iter++ < sets->max_iter)
			{
				c->x2 = pow(c->x, 2.0) - pow(c->y, 2.0);
				c->y = 2 * c->x * c->y + sets->c_y;
				c->x = c->x2 + sets->c_x;
			}
			set_pixel_color(sets, c->iter, colors);
		}
	}
}

void	draw_mandelbrot(t_settings *sets, t_complex *c, int *colors)
{
	if (sets->sc)
		reset_c(sets);
	c->row = 0;
	c->col = 0;
	while (c->row++ < sets->height)
	{
		c->col = 0;
		c->c_im = sets->y_min + sets->c_y * c->row;
		while (c->col++ < sets->width)
		{
			is_bounded(c, sets);
			set_pixel_color(sets, c->iter, colors);
		}
	}
}
