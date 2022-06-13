#include "fractol.h"

void	error(char *msg)
{
	perror(msg);
	exit(1);
}

int	destroy(t_settings *sets)
{
	mlx_destroy_image(sets->mlx, sets->img);
	mlx_destroy_window(sets->mlx, sets->win);
	exit(0);
}

void	arg_error(int size, char **sets_available)
{
	int	i;

	i = 0;
	printf("Available sets: ");
	while (i < size - 1)
		printf("%s, ", sets_available[i++]);
	printf("%s.\n", sets_available[i++]);
	exit(1);
}
