/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 15:33:07 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/04 18:06:46 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	empty_dollar(t_exp *exp, t_list **l_tmp)
{
	char	*str;

	str = ft_strdup("$");
	if (!str)
		return (ERR);
	*l_tmp = ft_lstnew(str);
	if (!*l_tmp)
	{
		free(str);
		return (ERR);
	}
	ft_lstadd_back(exp->lst, *l_tmp);
	return (OK);
}

int	dollar_answ(t_exp *exp)
{
	char	*str;
	t_list	*lst;

	if (exp->word[exp->i + 1] == '?')
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
		exp->i += 2;
		return (2);
	}
	return (OK);
}

int	expand_var_end(int k, t_list *env, t_exp *exp)
{
	char	*key;
	t_dict	*tmp;
	t_list	*l_tmp;

	key = ft_calloc(k + 1, sizeof(char));
	if (!key)
		return (ERR);
	ft_memcpy(key, &(exp->word)[exp->i - k], k);
	tmp = get_var(key, env);
	free(key);
	if (!tmp)
		return (OK);
	key = ft_strdup(tmp->value);
	if (!key)
		return (ERR);
	l_tmp = ft_lstnew(key);
	if (!l_tmp)
		return (free_simple(key, 0, ERR));
	ft_lstadd_back(exp->lst, l_tmp);
	return (OK);
}

int	expand_var(t_list *env, t_exp *exp)
{
	int		k;
	t_list	*l_tmp;

	k = dollar_answ(exp);
	if (k == 2)
		return (OK);
	else if (k == ERR)
		return (ERR);
	while (exp->word[++exp->i] && (
			ft_isalnum(exp->word[exp->i]) || exp->word[exp->i] == '_'))
		k++;
	if (!k && empty_dollar(exp, &l_tmp) == ERR)
		return (ERR);
	else if (!k)
		return (OK);
	if (expand_var_end(k, env, exp) == ERR)
		return (ERR);
	return (OK);
}
