#ifndef FRACTOL_H
# define FRACTOL_H

# define WIDTH 1000
# define HEIGHT 1000
# define TITLE "FRACTOL"
# define MAX_ITER 50
# define SIZE 4.0

# define SET1 "Mandelbrot"
# define SET2 "Julia"
# define SETS_SIZE 2

# include <mlx.h>
# include "libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include "colors.h"

typedef struct s_settings
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
	int		set_id;
	double	x_min;
	double	x_max;
	double	y_min;
	double	y_max;
	double	c_x;
	double	c_y;
	int		max_iter;
	int		sc;
	int		color;
	int		animate;
	double	speed;
	double	r;
	double	j_size;
	double	j_x_pl;
	double	j_y_pl;
}	t_settings;

typedef struct s_complex
{
	double		row;
	double		col;
	long double	c_re;
	long double	c_im;
	long double	x;
	long double	y;
	long double	x2;
	long double	y2;
	int			iter;
}	t_complex;

void	reset(t_settings *sets);
void	draw_julia(t_settings *sets, t_complex *c, int *colors);
void	draw_mandelbrot(t_settings *sets, t_complex *c, int *colors);
char	*put_pixel(int color, char *addr);
void	set_pixel_color(t_settings *sets, int iter, int *colors);

int		key_hook(int keycode, t_settings *sets);
int		mouse_hook(int button, int x, int y, t_settings *sets);
void	move(int keycode, t_settings *sets);
void	change_depth(int keycode, t_settings *sets);
void	change_color(t_settings *sets);

void	julia_hook(int keycode, t_settings *sets);
int		julia_loop(t_settings *sets);
void	julia_move(int keycode, t_settings *sets);
void	julia_zoom(int button, int x, int y, t_settings *sets);

void	switch_animate(t_settings *sets);

void	draw(t_settings *sets);
void	set_img(t_settings *sets);
int		destroy(t_settings *sets);

void	error(char *msg);
void	arg_error(int size, char **sets_available);

#endif
