/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 15:33:05 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/03 22:04:18 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_heredoc_d_quote(t_exp *exp)
{
	int		k;
	char	*inner;
	t_list	*l_tmp;

	k = 0;
	while (exp->word[++exp->i] && exp->word[exp->i] != '\"')
		k++;
	if (!k)
		return (exp->i++ && 0);
	inner = ft_calloc(k + 1, sizeof(char));
	if (!inner)
		return (ERR);
	ft_memcpy(inner, &exp->word[exp->i - k], k);
	l_tmp = ft_lstnew(inner);
	if (!l_tmp)
	{
		free(inner);
		return (ERR);
	}
	ft_lstadd_back(exp->lst, l_tmp);
	return (exp->i++ && 0);
}

int	expand_word_heredoc(char **word, t_list *env)
{
	static t_exp	*exp;
	t_list			*tmp;
	char			*c;

	if (init_exp(&exp, *word) == ERR)
		return (ERR);
	while (exp->word[++exp->i])
	{
		while (exp->word[exp->i] && exp->word[exp->i] == '$')
			if (expand_var(env, exp) == ERR)
				return (clr_exp(exp, ERR));
		if (!exp->word[exp->i])
			break ;
		c = ft_calloc(2, 1);
		if (!c)
			return (clr_exp(exp, ERR));
		*c = exp->word[exp->i];
		tmp = ft_lstnew((void *)c);
		if (!tmp)
			return (free_simple(c, 0, clr_exp(exp, ERR)));
		ft_lstadd_back(exp->lst, tmp);
	}
	if (ft_lstjoin(exp->lst, word) == ERR)
		return (free_simple(c, tmp, clr_exp(exp, ERR)));
	return (0);
}

int	expand_hquotes(t_exp *exp)
{
	while (exp->word[exp->i] && exp->word[exp->i] == '\'')
	{
		if (expand_single_quote(exp) == ERR)
			return (clr_exp(exp, ERR));
	}
	while (exp->word[exp->i] && exp->word[exp->i] == '\"')
	{
		if (expand_heredoc_d_quote(exp) == ERR)
			return (clr_exp(exp, ERR));
	}
	return (OK);
}

int	expand_key_heredoc(char **word)
{
	static t_exp	*exp;
	t_list			*tmp;
	char			*c;

	if (init_exp(&exp, *word) == ERR)
		return (ERR);
	while (exp->word[++exp->i])
	{
		expand_hquotes(exp);
		if (!exp->word[exp->i])
			break ;
		c = ft_calloc(2, 1);
		if (!c)
			return (clr_exp(exp, ERR));
		*c = exp->word[exp->i];
		tmp = ft_lstnew((void *)c);
		if (!tmp)
			return (free_simple(c, 0, clr_exp(exp, ERR)));
		ft_lstadd_back(exp->lst, tmp);
	}
	if (ft_lstjoin(exp->lst, word))
		return (free_simple(c, tmp, clr_exp(exp, ERR)));
	return (0);
}
