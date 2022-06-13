#include "content.h"

int	get_value(t_list *lst)
{
	if (!lst)
		return (0);
	return (((t_item *) lst->content)->value);
}

int	get_index(t_list *lst)
{
	if (!lst)
		return (0);
	return (((t_item *) lst->content)->index);
}

int	get_flag(t_list *lst)
{
	if (!lst)
		return (0);
	return (((t_item *) lst->content)->flag);
}
