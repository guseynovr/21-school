#include "content.h"

void	set_value(t_list *lst, int value)
{
	if (!lst)
		return ;
	((t_item *) lst->content)->value = value;
}

void	set_index(t_list *lst, int index)
{
	if (!lst)
		return ;
	((t_item *) lst->content)->index = index;
}

void	set_flag(t_list *lst, int flag)
{
	if (!lst)
		return ;
	((t_item *) lst->content)->flag = flag;
}
