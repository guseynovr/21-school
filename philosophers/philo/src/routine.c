/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 20:02:59 by dgidget           #+#    #+#             */
/*   Updated: 2021/08/20 10:42:57 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	struct timeval	tv;

	if (philo->args->stopped)
	{
		pthread_mutex_unlock(&philo->left->mutex);
		pthread_mutex_unlock(&philo->right->mutex);
		return ;
	}
	print_state(EATING, COLOR_GREEN, philo);
	gettimeofday(&tv, NULL);
	msleep(set_timestamp(&tv, &philo->last_meal), philo->args->tte);
	pthread_mutex_unlock(&philo->left->mutex);
	pthread_mutex_unlock(&philo->right->mutex);
	philo->meals++;
}

void	p_sleep(t_philo *philo)
{
	if (philo->args->stopped)
		return ;
	print_state(SLEEPING, COLOR_YELLOW, philo);
	msleep(philo->last_meal + philo->args->tte, philo->args->tts);
}

int	try2takeafork(t_fork *fork, t_philo *philo)
{
	if (fork->last_id != philo->id)
	{
		pthread_mutex_lock(&fork->mutex);
		print_state(FORK, COLOR_KMAG, philo);
		fork->last_id = philo->id;
		return (1);
	}
	else
		return (0);
}

void	think(t_philo *philo)
{
	int	i;

	if (philo->args->stopped)
		return ;
	print_state(THINKING, COLOR_CYAN, philo);
	i = 0;
	while (i < 2)
	{
		i += try2takeafork(philo->left, philo);
		if (philo->args->stopped)
		{
			pthread_mutex_unlock(&philo->left->mutex);
			pthread_mutex_unlock(&philo->right->mutex);
			return ;
		}
		i += try2takeafork(philo->right, philo);
		if (i < 2)
			pthread_mutex_unlock(&philo->left->mutex);
	}
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	while (!philo->args->stopped)
	{
		think(philo);
		eat(philo);
		p_sleep(philo);
	}
	return (data);
}
