/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 20:03:44 by dgidget           #+#    #+#             */
/*   Updated: 2021/08/20 13:33:16 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_and_return(char *msg, int ret)
{
	printf("%s", msg);
	return (ret);
}

long long	set_timestamp(struct timeval *tv, long long *ts)
{
	*ts = tv->tv_sec * 1000 + tv->tv_usec / 1000;
	return (*ts);
}

void	free_all(void *forks, void *philos, void *tids, pthread_mutex_t *mutex)
{
	int		i;
	t_fork	*f;
	t_philo	*ph;

	f = (t_fork *) forks;
	ph = (t_philo *) philos;
	i = -1;
	while (++i < ph->args->nbr_phs)
		pthread_mutex_destroy(&f[i].mutex);
	free(forks);
	free(philos);
	free(tids);
	pthread_mutex_destroy(mutex);
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
