/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 15:32:57 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/03 15:36:33 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long	ft_atoi_lvl(const char *str)
{
	long	n;
	int		sign;

	n = 0;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
		n = n * 10 + *str++ - '0';
	if (!(*str))
		return (n * sign);
	return (0);
}

int	set_shell_env(t_list **env)
{
	char	*str;

	str = getcwd(0, 0);
	if (set_var("SHELL", str, env) == ERR)
		return (free_simple(str, 0, ERR));
	return (OK);
}

int	set_shelllvl(t_list **env)
{
	long	start_shlvl;
	t_dict	*shll;

	if (set_shell_env(env) == ERR)
		return (ERR);
	shll = get_var("SHLVL", *env);
	if (!shll)
	{
		if (set_var("SHLVL", "1", env) == ERR)
			return (ERR);
		return (OK);
	}
	start_shlvl = ft_atoi_lvl(shll->value);
	if (start_shlvl < 0)
		start_shlvl = 0;
	else
		start_shlvl++;
	if (set_var("SHLVL", ft_itoa((int)start_shlvl), env) == ERR)
		return (ERR);
	return (OK);
}
