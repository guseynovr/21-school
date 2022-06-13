/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 19:16:25 by ruslan            #+#    #+#             */
/*   Updated: 2021/10/04 18:37:49 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_hand_too(int signal)
{
	extern int	rl_end;
	int			k;

	k = rl_end + ft_strlen(SH_NAME) + 2;
	if (signal == SIGINT)
	{
		while (k--)
			printf("\e[C");
		printf("\e[K\n");
		rl_replace_line("", 0);
	}
	else if (signal == SIGQUIT)
		write(1, "\e[K", 3);
}

void	sig_hand_main(int signal)
{
	sig_hand_too(signal);
	rl_on_new_line();
	if (g_sh.status != SH_EXEC)
		rl_redisplay();
}

void	signal_quit(int signal)
{
	if (signal == SIGQUIT)
		rl_replace_line("", 0);
}

/*  */
int	event(void)
{
	return (OK);
}

void	signal_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		g_sh.status = 1;
		g_sh.last_return = 1;
		rl_done = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
