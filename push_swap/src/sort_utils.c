#include "push_swap.h"

int	optimize_place(int place, int size)
{
	if (size > 2 && place > size / 2)
		return (place - size);
	return (place);
}

void	mv_top(int place, t_list **lst, char *ro, char *rro)
{
	while (place > 0)
	{
		rotate(lst, 0, ro);
		place--;
	}
	while (place < 0)
	{
		reverse_rotate(lst, 0, rro);
		place++;
	}
}

void	mark_sorted(t_list **a, t_list **b, t_info *info, int in_a)
{
	if (!in_a)
		push(b, a, "pa\n");
	set_flag(*a, -1);
	if (*b && get_index(*b) != info->next
		&& !(get_index(*b) >= info->mid + 1 && get_index(*b) <= info->max))
		rotate(a, b, "rr\n");
	else
		rotate(a, 0, "ra\n");
	info->next++;
}

void	calc_info(t_list *a, t_info *info)
{
	int	max;
	int	flag;

	max = 0;
	flag = get_flag(a);
	while (a && get_flag(a) == flag)
	{
		if (get_index(a) > max)
			max = get_index(a);
		a = a->next;
	}
	info->max = max;
	info->mid = (info->max - info->next) / 2 + info->next;
}

int	is_sorted(t_list *a, t_list *b, int end)
{
	t_list	*tmp;

	tmp = a;
	if (b)
		return (0);
	if (!a && !b)
		exit(0);
	while (tmp && tmp->next)
	{
		if (cmp(tmp, tmp->next) > 0)
			return (0);
		tmp = tmp->next;
	}
	free_lst(a);
	if (end)
		exit(0);
	return (1);
}
