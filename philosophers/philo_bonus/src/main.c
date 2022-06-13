/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 13:49:33 by dgidget           #+#    #+#             */
/*   Updated: 2021/08/25 11:33:34 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	declare_death(t_philo *philo)
{
	struct timeval	tv;
	long long		current;
	int				i;

	sem_wait(philo->args->sem_table);
	gettimeofday(&tv, NULL);
	set_timestamp(&tv, &current);
	printf("%s" "%lli \t%i %s\n" COLOR_RESET, COLOR_RED,
		current - philo->args->ts, philo->id, DIED);
	i = -1;
	while (++i < philo->args->nbr_phs)
		kill(philo->args->pids[i], 0);
}

int	create_philos(t_args *args)
{
	// pid_t	*pids;
	t_philo	philo;
	int		i;

	philo.id = 0;
	philo.args = args;
	philo.meals = 0;
	philo.last_meal = args->ts;
	args->pids = malloc(sizeof(pid_t) * args->nbr_phs);
	if (!args->pids)
		return (ERR);
	i = -1;
	while (++i < args->nbr_phs)
	{
		philo.id++;
		args->pids[i] = fork();
		if (args->pids[i] == -1)
			return (ERR);
		if (!args->pids[i])
			routine(&philo);
	}
	// *ps = pids;
	return (OK);
}

int	main(int argc, char **argv)
{
	t_args	args;
	// pid_t	*pids;
	int		i;
	int		stat_loc;

	if (init_args(&args, argc, ++argv) == ERR
		|| create_philos(&args) == ERR)
		return (1);
	i = -1;
	// while (++i < args.nbr_phs)
	// 	kill(pids[i], 0);
	while (++i < args.nbr_phs)
		waitpid(args.pids[i], &stat_loc, WUNTRACED);
	sem_unlink(args.forks_name);
	i = -1;
	while (++i < args.nbr_phs)
		kill(args.pids[i], 0);
	free_all(args.pids);
	return (0);
}
