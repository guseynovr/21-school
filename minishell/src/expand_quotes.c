/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 15:33:02 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/04 18:12:30 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_single_quote(t_exp *exp)
{
	int		k;
	char	*inner;
	t_list	*l_tmp;

	k = 0;
	while (exp->word[++exp->i] && exp->word[exp->i] != '\'')
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

int	expand_var_in_q_sub(char *str, int *i, t_exp *exp, char **key)
{
	int		k;
	t_list	*tmp;

	k = 0;
	while (str[++(*i)] && (ft_isalnum(str[(*i)]) || str[*i] == '_'))
		k++;
	*key = ft_calloc(k + 1, sizeof(char));
	if (!*key)
		return (ERR);
	if (!k && empty_dollar(exp, &tmp) == ERR)
	{
		ft_lstclear(exp->lst, free);
		return (free_simple(*key, 0, ERR));
	}
	else if (!k)
	{
		free(*key);
		return (OK);
	}
	ft_memcpy(*key, &str[*i - k], k);
	return (END);
}

int	expand_var_in_q(char *str, t_list *env, t_exp *exp, int *i)
{
	int		k;
	char	*key;
	t_dict	*env_dict;
	t_list	*tmp;

	k = dollar_answ_in_q(exp, str, i);
	if (k != END)
		return (k);
	k = expand_var_in_q_sub(str, i, exp, &key);
	if (k != END)
		return (k);
	env_dict = get_var(key, env);
	free(key);
	if (!env_dict)
		return (OK);
	key = ft_strdup(env_dict->value);
	tmp = ft_lstnew(key);
	if (!key || !tmp)
	{
		ft_lstclear(exp->lst, free);
		return (free_simple(key, tmp, ERR));
	}
	ft_lstadd_back(exp->lst, tmp);
	return (OK);
}

int	setting_var(char **inner, t_list *env, t_exp *exp)
{
	char	*tmp;
	int		i;

	tmp = *inner;
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] && tmp[i] != '$')
		{
			if (init_sym(tmp, i, exp) == ERR)
				return (ERR);
		}
		else
		{
			while (tmp[i] && tmp[i] == '$')
				if (expand_var_in_q(tmp, env, exp, &i) == ERR)
					return (ERR);
			continue ;
		}
		i++;
	}
	return (OK);
}

int	expand_double_quote(t_exp *exp, t_list *env)
{
	int		k;
	char	*inner;

	k = 0;
	while (exp->word[++exp->i] && exp->word[exp->i] != '\"')
		k++;
	if (!k)
		return (exp->i++ && OK);
	inner = ft_calloc(k + 1, sizeof(char));
	if (!inner)
		return (ERR);
	ft_memcpy(inner, &exp->word[exp->i - k], k);
	if (setting_var(&inner, env, exp) == ERR)
		return (free_simple(inner, 0, ERR));
	return (exp->i++ && OK);
}
