#include "push_swap.h"

void	sort_three(t_list **lst, int in_a)
{
	int		max;
	char	*sw;
	char	*ro;
	char	*rro;

	if (in_a)
	{
		sw = "sa\n";
		ro = "ra\n";
		rro = "rra\n";
	}
	else
	{
		sw = "sb\n";
		ro = "rb\n";
		rro = "rrb\n";
	}
	max = find_max(*lst);
	if (max == 0)
		rotate(lst, 0, ro);
	else if (max == 1)
		reverse_rotate(lst, 0, rro);
	if (*lst && (*lst)->next && cmp(*lst, (*lst)->next) > 0)
		swap(lst, 0, sw);
}

void	sort_five(t_list **a, t_list **b)
{
	while (ft_lstsize(*a) > 3)
	{
		mv_top(optimize_place(find_min(*a), ft_lstsize(*a)), a, "ra\n", "rra\n");
		push(a, b, "pb\n");
	}
	sort_three(a, 1);
	while (*b)
		push(b, a, "pa\n");
	is_sorted(*a, *b, EXIT);
}

void	sort_five_r(t_list **a, t_list **b, t_info *info)
{
	while (ft_lstsize(*b) > 3)
	{
		mv_top(optimize_place(find_max(*b), ft_lstsize(*b)), b, "rb\n", "rrb\n");
		push(b, a, "pa\n");
	}
	sort_three(b, 0);
	while (*b)
	{
		push(b, a, "pa\n");
		while (get_index(*a) == info->next)
			mark_sorted(a, b, info, 1);
	}
}

int	main(int argc, char **argv)
{
	t_list	*stack_a;
	t_list	*stack_b;

	stack_a = 0;
	stack_b = 0;
	stack_a = init_stack(argc, argv);
	set_indexes(stack_a);
	is_sorted(stack_a, stack_b, EXIT);
	sort(&stack_a, &stack_b);
}
