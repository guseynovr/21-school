/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:34:13 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 16:34:13 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cpy_lst;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	cpy_lst = *lst;
	while (cpy_lst->next)
		cpy_lst = cpy_lst->next;
	cpy_lst->next = new;
}
