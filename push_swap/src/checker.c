#include "init_stack.h"
#include "content.h"
#include "operations.h"
#include "consts.h"
#include "get_next_line.h"
#include "validation.h"

int	is_sorted(t_list *a, t_list *b, int end);

long	cmp(t_list *lst1, t_list *lst2)
{
	long	i1;
	long	i2;

	if (!lst1)
		i1 = 0;
	else
		i1 = get_value(lst1);
	if (!lst2)
		i2 = 0;
	else
		i2 = get_value(lst2);
	return (i1 - i2);
}

void	exec_op(t_list **a, t_list **b, char *s)
{
	if (!ft_strcmp(s, "sa"))
		swap(a, 0, 0);
	else if (!ft_strcmp(s, "sb"))
		swap(b, 0, 0);
	else if (!ft_strcmp(s, "ss"))
		swap(a, b, 0);
	else if (!ft_strcmp(s, "pa"))
		push(b, a, 0);
	else if (!ft_strcmp(s, "pb"))
		push(a, b, 0);
	else if (!ft_strcmp(s, "ra"))
		rotate(a, 0, 0);
	else if (!ft_strcmp(s, "rb"))
		rotate(b, 0, 0);
	else if (!ft_strcmp(s, "rr"))
		rotate(a, b, 0);
	else if (!ft_strcmp(s, "rra"))
		reverse_rotate(a, 0, 0);
	else if (!ft_strcmp(s, "rrb"))
		reverse_rotate(b, 0, 0);
	else if (!ft_strcmp(s, "rrr"))
		reverse_rotate(a, b, 0);
	else
		error(*a, 0, 1);
}

int	main(int argc, char **argv)
{
	char	*s;
	int		ret;
	t_list	*a;
	t_list	*b;

	a = 0;
	b = 0;
	a = init_stack(argc, argv);
	s = 0;
	ret = get_next_line(0, &s);
	while (ret >= 0)
	{
		if (ret == 0)
			break ;
		exec_op(&a, &b, s);
		free(s);
		s = 0;
		ret = get_next_line(0, &s);
	}
	if (is_sorted(a, b, STAY))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
}
