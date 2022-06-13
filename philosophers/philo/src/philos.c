/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 20:14:40 by dgidget           #+#    #+#             */
/*   Updated: 2021/08/25 21:47:33 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(char *msg, char *color, t_philo *philo)
{
	struct timeval	tv;
	long long		current;

	pthread_mutex_lock(&philo->args->mutex_speech);
	if (philo->args->stopped)
	{
		pthread_mutex_unlock(&philo->args->mutex_speech);
		return ;
	}
	if (gettimeofday(&tv, NULL) < 0)
	{
		printf(ERRTIME);
		return ;
	}
	set_timestamp(&tv, &current);
	printf("%s" "%lli \t%i %s\n" COLOR_RESET,
		color, current - philo->args->ts, philo->id, msg);
	pthread_mutex_unlock(&philo->args->mutex_speech);
}

void	declare_death(t_philo *philo)
{
	struct timeval	tv;
	long long		current;

	pthread_mutex_lock(&philo->args->mutex_speech);
	gettimeofday(&tv, NULL);
	set_timestamp(&tv, &current);
	printf("%s" "%lli \t%i %s\n" COLOR_RESET, COLOR_RED,
		current - philo->args->ts, philo->id, DIED);
}

void	setup_philo(t_philo *philo, t_fork *forks, t_args *args, int i)
{
	philo->id = i + 1;
	if (i % 2 == 0)
	{
		philo->left = &forks[i];
		philo->right = &forks[(i + 1) % args->nbr_phs];
	}
	else
	{
		philo->left = &forks[(i + 1) % args->nbr_phs];
		philo->right = &forks[i];
	}
	philo->args = args;
	philo->last_meal = args->ts;
	philo->meals = 0;
}

pthread_t	*create_philos(t_args *args, t_fork *forks,
t_philo **philos)
{
	pthread_t	*tids;
	t_philo		*philo;
	int			i;

	tids = malloc(sizeof(pthread_t) * args->nbr_phs);
	if (!tids)
		return (NULL);
	philo = malloc(sizeof(t_philo) * args->nbr_phs);
	if (!philo)
		return (NULL);
	i = -1;
	while (++i < args->nbr_phs)
	{
		setup_philo(&philo[i], forks, args, i);
		if (pthread_create(&tids[i], NULL, routine, &philo[i]))
		{
			free_all(forks, philos, tids, &args->mutex_speech);
			return (NULL);
		}
	}
	*philos = philo;
	return (tids);
}

void	join_philos(pthread_t *philos, t_args *args, pthread_t monitor)
{
	int		i;
	void	*ret;

	i = -1;
	while (++i < args->nbr_phs)
		pthread_join(philos[i], &ret);
	pthread_join(monitor, &ret);
}
