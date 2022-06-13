#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*head;
	t_list	*temp;

	head = *lst;
	while (head)
	{
		temp = head;
		head = head->next;
		del(temp->content);
		free(temp);
	}
	*lst = 0;
}
