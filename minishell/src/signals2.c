/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:37:05 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/04 18:37:23 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_heredoc(char *welc)
{
	extern int	rl_end;
	int			i;

	printf("welc: %s\n", welc);
	if (welc)
	{
		i = ft_strlen(welc) + ft_strlen(SH_NAME) + 1;
		printf("\e[A");
		while (i--)
			printf("\e[C");
	}
}

void	my_exit(char *welc)
{
	extern int	rl_end;
	int			i;

	if (welc)
	{
		i = ft_strlen(welc) + rl_end + 2;
		printf("\e[A");
		while (i--)
			printf("\e[C");
		printf("exit\n");
	}
	exit(g_sh.last_return);
}
