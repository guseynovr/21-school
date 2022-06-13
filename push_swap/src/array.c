#include "push_swap.h"

static int	*init_arr(t_list *lst, int size)
{
	int	*arr;

	arr = malloc(sizeof(int) * size);
	if (!arr)
		error(lst, 0, 0);
	size = 0;
	while (lst)
	{
		arr[size++] = get_value(lst);
		lst = lst->next;
	}
	return (arr);
}

void	set_indexes(t_list *a)
{
	int		*arr;
	int		size;
	int		i;

	size = ft_lstsize(a);
	arr = init_arr(a, size);
	quicksort(arr, 0, size - 1);
	while (a)
	{
		i = 0;
		while (get_value(a) != arr[i])
			i++;
		set_index(a, i + 1);
		a = a->next;
	}
	free(arr);
}
