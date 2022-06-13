#include "push_swap.h"

int	check_next(t_list **a, t_list **b, t_info *info, int in_a)
{
	t_list	**tmp;
	int		i;

	if (in_a)
		tmp = a;
	else
		tmp = b;
	i = 0;
	while (get_index(*tmp) == info->next)
	{
		mark_sorted(a, b, info, in_a);
		i++;
	}
	return (i);
}

void	next_half(t_info *info)
{
	info->max = info->mid;
	info->mid = (info->max - info->next) / 2 + info->next;
	info->flag++;
}

void	mv_a(t_list **a, t_list **b, t_info *info)
{
	int		n;

	calc_info(*b, info);
	if (info->mid < info->next)
		return ;
	info->flag++;
	while (ft_lstsize(*b) > 5)
	{
		n = next(*b, info->mid + 1, info->max);
		while (n != ft_lstsize(*b))
		{
			check_next(a, b, info, 0);
			if (get_index(*b) >= info->mid + 1 && get_index(*b) <= info->max)
			{
				push(b, a, "pa\n");
				set_flag(*a, info->flag);
			}
			else
				rotate(b, 0, "rb\n");
			n = next(*b, info->mid + 1, info->max);
		}
		next_half(info);
	}
	sort_five_r(a, b, info);
}

void	init_info(t_info *info, t_list *a)
{
	info->next = 1;
	info->max = ft_lstsize(a);
	info->mid = (info->max + 1) / 2;
	info->flag = 0;
}

void	sort(t_list **a, t_list **b)
{
	t_info	info;
	int		i;
	int		fl;

	if (ft_lstsize(*a) < 6)
		sort_five(a, b);
	init_info(&info, *a);
	i = info.next - 1;
	while (i++ < info.mid)
	{
		mv_top(next(*a, info.next, info.mid), a, "ra\n", "rra\n");
		push(a, b, "pb\n");
	}
	mv_a(a, b, &info);
	while (!is_sorted(*a, *b, EXIT))
	{
		fl = get_flag(*a);
		info.flag = fl;
		while (fl == get_flag(*a))
		{
			if (!check_next(a, b, &info, 1))
				push(a, b, "pb\n");
		}
		mv_a(a, b, &info);
	}
}
