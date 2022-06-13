/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:34:23 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 16:34:28 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*buf;

	if (!lst || !del)
		return ;
	while ((*lst)->next)
	{
		del((*lst)->content);
		buf = *lst;
		*lst = buf->next;
		free(buf);
	}
	del((*lst)->content);
	free(*lst);
	*lst = 0;
}
