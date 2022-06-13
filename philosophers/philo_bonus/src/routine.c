/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 07:54:09 by dgidget           #+#    #+#             */
/*   Updated: 2021/08/25 11:27:16 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	think(t_philo *philo)
{
	if (philo->args->stopped)
		return ;
	print_state(THINKING, COLOR_CYAN, philo);
	printf("TEST0\n");
	// sem_post(philo->args->sem_table);
	sem_wait(philo->args->sem_table);
	printf("TEST1\n");
	// sem_post(philo->args->sem_forks);
	sem_wait(philo->args->sem_forks);
	printf("TEST2\n");
	print_state(FORK, COLOR_KMAG, philo);
	sem_wait(philo->args->sem_forks);
	print_state(FORK, COLOR_KMAG, philo);
	sem_post(philo->args->sem_table);
}

void	eat(t_philo *philo)
{
	struct timeval	tv;

	if (philo->args->stopped)
	{
		sem_post(philo->args->sem_forks);
		sem_post(philo->args->sem_forks);
		return ;
	}
	print_state(EATING, COLOR_GREEN, philo);
	gettimeofday(&tv, NULL);
	msleep(set_timestamp(&tv, &philo->last_meal), philo->args->tte);
	sem_post(philo->args->sem_forks);
	sem_post(philo->args->sem_forks);
	philo->meals++;
}

void	p_sleep(t_philo *philo)
{
	if (philo->args->stopped)
		return ;
	print_state(SLEEPING, COLOR_YELLOW, philo);
	msleep(philo->last_meal + philo->args->tte, philo->args->tts);
}

void	*monitor_routine(void *data)
{
	struct timeval	tv;
	long long		now;
	long long		time_since_lm;
	t_philo			*philo;

	philo = (t_philo *) data;
	while (!philo->args->stopped)
	{
		gettimeofday(&tv, NULL);
		set_timestamp(&tv, &now);
		time_since_lm = now - philo->last_meal;
		if (time_since_lm >= philo->args->ttd)
		{
			philo->args->stopped = 1;
			declare_death(philo);
		}
		else if (philo->args->nbr_tte && philo->meals >= philo->args->nbr_tte)
			philo->args->stopped = 1;
	}
	return (data);
}

void	routine(t_philo *philo)
{
	pthread_t	monitor;
	// void 		*data;

	pthread_create(&monitor, NULL, monitor_routine, philo);
	pthread_detach(monitor);
	while (!philo->args->stopped)
	{
		think(philo);
		eat(philo);
		p_sleep(philo);
	}
	sem_close(philo->args->sem_forks);
	// pthread_join(monitor, &data);
	exit(0);
}
