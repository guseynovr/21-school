/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 13:49:31 by dgidget           #+#    #+#             */
/*   Updated: 2021/08/21 08:10:29 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_state(char *msg, char *color, t_philo *philo)
{
	struct timeval	tv;
	long long		current;

	if (philo->args->stopped)
		return ;
	gettimeofday(&tv, NULL);
	set_timestamp(&tv, &current);
	printf("%s" "%lli \t%i %s\n" COLOR_RESET,
		color, current - philo->args->ts, philo->id, msg);
}

int	error(char *s, int code)
{
	printf("%s\n", s);
	return (code);
}

long long	set_timestamp(struct timeval *tv, long long *ts)
{
	*ts = tv->tv_sec * 1000 + tv->tv_usec / 1000;
	return (*ts);
}

void	msleep(long long start, int msecs)
{
	struct timeval	tv;
	long long		cur;

	gettimeofday(&tv, NULL);
	set_timestamp(&tv, &cur);
	while (cur - start < msecs)
	{
		usleep(50);
		gettimeofday(&tv, NULL);
		set_timestamp(&tv, &cur);
	}
}

void	free_all()
{

}
