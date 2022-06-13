#include "push_swap.h"

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

int	find_min(t_list *lst)
{
	int		index;
	int		i;
	t_list	*min;

	i = 0;
	min = lst;
	index = 0;
	while (lst)
	{
		if (cmp(lst, min) < 0)
		{
			min = lst;
			index = i;
		}
		lst = lst->next;
		i++;
	}
	return (index);
}

int	find_max(t_list *lst)
{
	int		index;
	int		i;
	t_list	*max;

	i = 0;
	max = lst;
	index = 0;
	while (lst)
	{
		if (cmp(lst, max) > 0)
		{
			max = lst;
			index = i;
		}
		lst = lst->next;
		i++;
	}
	return (index);
}

static int	cmp_place(int i1, int i2, int size)
{
	if (i1 > size / 2)
		i1 -= size;
	if (i1 < 0)
		i1 = -i1;
	if (i2 < 0)
		i2 = -i2;
	return (i1 - i2);
}

long	next(t_list *lst, int min, int max)
{
	int	res;
	int	size;
	int	i;

	size = ft_lstsize(lst);
	i = 0;
	res = size;
	while (lst)
	{
		if (get_index(lst) >= min && get_index(lst) <= max
			&& cmp_place(i, res, size) < 0)
			res = optimize_place(i, size);
		i++;
		lst = lst->next;
	}
	return (res);
}
