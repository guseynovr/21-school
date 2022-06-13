/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:56:53 by ruslan            #+#    #+#             */
/*   Updated: 2021/10/01 13:36:11 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mexit(int argc, char **argv, t_list **env_lst)
{
	int	i;

	(void) env_lst;
	if (argc < 2)
		exit(g_sh.last_return % MAX_EXITCODE);
	i = -1;
	while (argv[1][++i])
	{
		if (!ft_isdigit(argv[1][i]))
			exit(g_sh.last_return % MAX_EXITCODE);
	}
	exit(ft_atoi(argv[1]));
}
