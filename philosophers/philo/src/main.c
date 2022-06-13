/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 12:46:17 by dgidget           #+#    #+#             */
/*   Updated: 2021/08/25 21:43:04 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_alive(t_philo *philo)
{
	struct timeval	tv;
	long long		now;
	long long		time_since_lm;

	gettimeofday(&tv, NULL);
	set_timestamp(&tv, &now);
	time_since_lm = now - philo->last_meal;
	if (time_since_lm >= philo->args->ttd)
	{
		philo->args->stopped = 1;
		declare_death(philo);
		return (0);
	}
	return (1);
}

void	*monitor_routine(void *data)
{
	t_args		*args;
	t_philo		*philos;
	int			i;
	int			meals;

	philos = (t_philo *) data;
	args = philos[0].args;
	i = -1;
	while (!args->stopped)
	{
		i = -1;
		meals = 0;
		while (++i < args->nbr_phs)
		{
			if (!is_alive(&philos[i]))
				break ;
			if (args->nbr_tte && philos[i].meals >= args->nbr_tte)
				meals++;
		}
		if (meals == args->nbr_phs)
			args->stopped = 1;
	}
	pthread_mutex_unlock(&args->mutex_speech);
	return (0);
}

int	main(int argc, char **argv)
{
	t_args			args;
	t_fork			*forks;
	t_philo			*philos;
	pthread_t		*tids;
	pthread_t		monitor;

	if (init_args(&args, argc, ++argv) == ERR)
		return (print_and_return(ERRARG, ERR));
	if (prepare(&forks, &args) == ERR)
		return (ERR);
	tids = create_philos(&args, forks, &philos);
	if (!tids)
		return (print_and_return(ERRTHREAD, ERR));
	if (pthread_create(&monitor, NULL, monitor_routine, philos))
	{
		free_all(forks, philos, tids, &args.mutex_speech);
		return (print_and_return(ERRTHREAD, ERR));
	}
	join_philos(tids, &args, monitor);
	free_all(forks, philos, tids, &args.mutex_speech);
}
