#include "content.h"
#include "validation.h"
#include "quicksort.h"

static int	in_list(t_list *lst, int num)
{
	int	p;

	while (lst)
	{
		p = ((t_item *) lst->content)->value;
		if (p == num)
			return (1);
		lst = lst->next;
	}
	return (0);
}

static void	add_items(char **args, t_list **stack)
{
	int		i;
	t_item	*item;

	i = 0;
	while (args[i])
		i++;
	while (i-- > 0)
	{
		if (!is_valid(args[i]))
			error(*stack, args, 1);
		item = malloc(sizeof(t_item));
		if (!item)
			error(*stack, args, 0);
		item->value = ft_atoi(args[i]);
		item->flag = 0;
		if (in_list(*stack, item->value))
			error(*stack, args, 1);
		ft_lstadd_front(stack, ft_lstnew(item));
	}
}

t_list	*init_stack(int argc, char **argv)
{
	t_list	*stack;
	char	**args;
	int		i;

	stack = 0;
	args = 0;
	if (argc < 2)
		exit(1);
	while (--argc > 0)
	{
		args = ft_split(argv[argc], ' ');
		if (!args)
			error(stack, args, 0);
		if (!*args)
			error(stack, args, 1);
		add_items(args, &stack);
		if (args)
		{
			i = 0;
			while (args[i])
				free(args[i++]);
			free(args);
		}
	}
	return (stack);
}
