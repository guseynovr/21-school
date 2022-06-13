#include "fractol.h"

void	set_img(t_settings *sets)
{
	sets->img = mlx_new_image(sets->mlx, sets->width, sets->height);
	if (!sets->img)
		error("mlx_new_image_error");
	sets->img_data = mlx_get_data_addr(sets->img, &sets->bpp,
			&sets->size_line, &sets->endian);
	if (!sets->img_data)
		error("mlx_get_data_addr_error");
}

void	init(t_settings *sets)
{
	sets->mlx = mlx_init();
	if (!sets->mlx)
		error("mlx_init_error");
	sets->width = WIDTH;
	sets->height = HEIGHT;
	sets->win = mlx_new_window(sets->mlx, sets->width, sets->height, TITLE);
	if (!sets->win)
		error("mlx_new_window_error");
	set_img(sets);
	sets->color = BROWN;
	reset(sets);
}

void	start(t_settings *sets)
{
	init(sets);
	mlx_mouse_hook(sets->win, mouse_hook, sets);
	mlx_hook(sets->win, 2, 1L << 0, key_hook, sets);
	mlx_hook(sets->win, 17, 0, destroy, sets);
	mlx_loop_hook(sets->mlx, julia_loop, sets);
	draw(sets);
	mlx_loop(sets->mlx);
}

int	is_set_available(int size, char **sets_available, char *arg)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (ft_strcmp(arg, sets_available[i]) == 0)
			return (i);
	}
	return (-1);
}

int	main(int argc, char **argv)
{
	char		*sets_available[SETS_SIZE];
	t_settings	sets;

	sets_available[0] = SET1;
	sets_available[1] = SET2;
	if (argc != 2)
		arg_error(SETS_SIZE, sets_available);
	sets.set_id = is_set_available(SETS_SIZE, sets_available, argv[1]);
	if (sets.set_id < 0)
		arg_error(SETS_SIZE, sets_available);
	start(&sets);
}
