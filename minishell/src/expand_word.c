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

int	init_exp(t_exp **exp, char *word)
{
	t_list	**lst;

	*exp = malloc(sizeof(t_exp) * 1);
	lst = malloc(sizeof(t_list *) * 1);
	if (!*exp || !lst)
		return (free_simple(*exp, lst, ERR));
	(*exp)->i = -1;
	(*exp)->word = word;
	*lst = 0;
	(*exp)->lst = lst;
	return (0);
}

int	ft_lstjoin(t_list **lst, char **word)
{
	char	*lst_str;
	t_list	*tmp;
	char	*new_word;
	int		i;
	int		k;

	tmp = *lst;
	new_word = ft_calloc(ft_len_content(tmp) + 1, sizeof(char));
	if (!new_word)
		return (ERR);
	i = 0;
	while (tmp)
	{
		k = 0;
		lst_str = tmp->content;
		while (lst_str[k])
			new_word[i++] = lst_str[k++];
		tmp = tmp->next;
	}
	ft_lstclear(lst, free);
	free(*word);
	*word = new_word;
	return (OK);
}

int	expand_word_sub(t_exp *exp, t_list *env)
{
	while (exp->word[exp->i] && exp->word[exp->i] == '$')
		if (expand_var(env, exp) == ERR)
			return (clr_exp(exp, ERR));
	while (exp->word[exp->i] && exp->word[exp->i] == '\'')
		if (expand_single_quote(exp) == ERR)
			return (clr_exp(exp, ERR));
	while (exp->word[exp->i] && exp->word[exp->i] == '\"')
		if (expand_double_quote(exp, env) == ERR)
			return (clr_exp(exp, ERR));
	return (OK);
}

int	expand_word(char **word, t_list *env)
{
	static t_exp	*exp;
	t_list			*tmp;
	char			*c;

	if (init_exp(&exp, *word) == ERR)
		return (ERR);
	while (exp->word[++exp->i])
	{
		if (expand_word_sub(exp, env) == ERR)
			return (ERR);
		if (!exp->word[exp->i])
			break ;
		c = ft_calloc(2, 1);
		if (!c)
			return (clr_exp(exp, ERR));
		*c = exp->word[exp->i];
		tmp = ft_lstnew((void *)c);
		if (!tmp)
			return (clr_exp(exp, ERR));
		ft_lstadd_back(exp->lst, tmp);
	}
	if (ft_lstjoin(exp->lst, word) == ERR)
		return (clr_exp(exp, ERR));
	free(exp);
	return (OK);
}
