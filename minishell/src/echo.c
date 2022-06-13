/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:20:21 by dgidget           #+#    #+#             */
/*   Updated: 2021/09/23 12:02:50 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(int argc, char **argv, t_list **env_lst)
{
	char	*end;
	int		i;

	(void) env_lst;
	end = "\n";
	if (argc > 1 && ft_strcmp(argv[1], "-n") == 0)
	{
		end = "";
		argv++;
	}
	i = 0;
	while (argv[++i])
	{
		if (i > 1)
			printf(" ");
		printf("%s", argv[i]);
	}
	printf("%s", end);
	return (OK);
}
