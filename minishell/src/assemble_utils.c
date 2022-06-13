/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 14:19:10 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/04 20:23:50 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirectadd_back(t_redirect **redirects, t_redirect *new)
{
	t_redirect	*head;

	if (!*redirects)
	{
		*redirects = new;
		return ;
	}
	head = *redirects;
	while (head->next)
		head = head->next;
	head->next = new;
}

void	redirectadd_front(t_redirect **redirects, t_redirect *new)
{
	if (!new)
		return ;
	new->next = *redirects;
	*redirects = new;
}

int	is_empty_var(char *s, t_list *env_lst)
{
	if (*s++ != '$')
		return (FALSE);
	if (!is_validname(s))
		return (FALSE);
	if (get_var(s, env_lst))
		return (FALSE);
	return (TRUE);
}
