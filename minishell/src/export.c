/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 15:10:07 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/03 16:41:46 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_var(char *s, t_list **env_lst)
{
	char	*key;
	char	*value;

	key = get_key(s);
	value = get_value(s);
	if (!key || !value)
		return (free_simple(key, value, ERR));
	if (!is_validname(key))
	{
		error_export("export", s);
		return (free_simple(key, value, OK));
	}
	if (!ft_strcmp(value, s))
		return (free_simple(key, value, OK));
	if (set_var(key, value, env_lst) == ERR)
		return (free_simple(key, value, ERR));
	return (free_simple(key, value, OK));
}

int	export(int argc, char **argv, t_list **env_lst)
{
	if (argc < 2)
	{
		ft_lstiter(*env_lst, print_env_lst);
		return (OK);
	}
	while (*++argv)
	{
		if (add_var(*argv, env_lst) == ERR)
			return (error_stdfunc("maloc"));
	}
	return (OK);
}
