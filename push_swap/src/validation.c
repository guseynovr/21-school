#include "push_swap.h"

static int	valid_format(char *str)
{
	int	d_count;

	if (!str)
		return (0);
	while (*str && *str == ' ')
		str++;
	if (*str && (*str == '-' || *str == '+'))
		str++;
	d_count = 0;
	while (*str && ft_isdigit(*str))
	{
		str++;
		d_count++;
	}
	if (!*str && d_count > 0)
		return (1);
	return (0);
}

int	is_valid(char *s)
{
	long	num;
	int		is_int_bounded;

	num = ft_atol(s);
	is_int_bounded = num >= INT_MIN && num <= INT_MAX;
	return (is_int_bounded && valid_format(s));
}

void	free_lst(t_list *stack)
{
	t_list	*tmp;

	while (stack)
	{
		tmp = stack->next;
		free(stack->content);
		free(stack);
		stack = tmp;
	}
}

void	error(t_list *stack, char **args, int format_error)
{
	int		i;

	free_lst(stack);
	i = 0;
	if (args)
		while (args[i])
			free(args[i++]);
	free(args);
	if (format_error)
	{
		write(1, "Error\n", 6);
		exit(1);
	}
	exit(ENOMEM);
}
