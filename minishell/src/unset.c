/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 10:43:35 by ruslan            #+#    #+#             */
/*   Updated: 2021/10/02 16:45:59 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(int argc, char **argv, t_list **env_lst)
{
	char	*key;

	if (argc < 2)
		return (OK);
	while (*++argv)
	{
		key = get_key(*argv);
		if (!key)
			return (error_stdfunc("malloc"));
		if (!is_validname(key))
		{
			error_export("unset", key);
			free(key);
			argv++;
			continue ;
		}
		del_var(key, env_lst);
		free(key);
	}
	return (OK);
}
