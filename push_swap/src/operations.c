#include "libft.h"

void	swap(t_list **stack, t_list **second, char *s)
{
	t_list	*tmp;
	t_list	*head;

	if (stack && second)
	{
		swap(stack, 0, 0);
		swap(second, 0, 0);
		ft_putstr_fd(s, 1);
		return ;
	}
	if (!stack || !*stack || !(*stack)->next)
		return ;
	head = *stack;
	tmp = head->next;
	head->next = head->next->next;
	tmp->next = head;
	*stack = tmp;
	ft_putstr_fd(s, 1);
}

void	push(t_list **from, t_list **to, char *s)
{
	t_list	*tmp;

	if (!*from)
		return ;
	tmp = (*from)->next;
	ft_lstadd_front(to, *from);
	*from = tmp;
	ft_putstr_fd(s, 1);
}

void	rotate(t_list **stack, t_list **second, char *s)
{
	t_list	*tmp;

	if (stack && second)
	{
		rotate(stack, 0, 0);
		rotate(second, 0, 0);
		ft_putstr_fd(s, 1);
		return ;
	}
	if (!*stack || !(*stack)->next)
		return ;
	tmp = (*stack)->next;
	ft_lstadd_back(stack, *stack);
	(*stack)->next = 0;
	*stack = tmp;
	ft_putstr_fd(s, 1);
}

void	reverse_rotate(t_list **stack, t_list **second, char *s)
{
	t_list	*tmp;

	if (stack && second)
	{
		reverse_rotate(stack, 0, 0);
		reverse_rotate(second, 0, 0);
		ft_putstr_fd(s, 1);
		return ;
	}
	if (!stack || !*stack || !(*stack)->next)
		return ;
	tmp = *stack;
	while (tmp->next->next)
		tmp = tmp->next;
	ft_lstadd_front(stack, tmp->next);
	tmp->next = 0;
	ft_putstr_fd(s, 1);
}
