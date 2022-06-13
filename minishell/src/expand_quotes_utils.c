/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 15:33:07 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/04 14:40:32 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_len_content(t_list *lst)
{
	int	result;

	result = 0;
	while (lst)
	{
		result += (int)ft_strlen(lst->content);
		lst = lst->next;
	}
	return (result);
}

int	init_sym(char *tmp, int i, t_exp *exp)
{
	char	*c;
	t_list	*lst;

	c = ft_calloc(2, 1);
	if (!c)
		return (ERR);
	*c = tmp[i];
	lst = ft_lstnew(c);
	if (!lst)
	{
		free(c);
		return (ERR);
	}
	ft_lstadd_back(exp->lst, lst);
	return (OK);
}

int	dollar_answ_in_q(t_exp *exp, char *s, int *i)
{
	char	*str;
	t_list	*lst;

	if (s[*i + 1] == '?')
	{
		str = ft_itoa(g_sh.last_return);
		if (!str)
			return (ERR);
		lst = ft_lstnew(str);
		if (!lst)
		{
			free(str);
			return (ERR);
		}
		ft_lstadd_back(exp->lst, lst);
		*i += 2;
		return (2);
	}
	return (END);
}
