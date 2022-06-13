/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 20:00:39 by dgidget           #+#    #+#             */
/*   Updated: 2021/08/20 10:29:34 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_parameter(char *s)
{
	int	n;

	n = 0;
	while (*s && *s >= '0' && *s <= '9')
		n = n * 10 + *s++ - '0';
	if (*s && (*s < '0' || *s > '9'))
		return (-1);
	return (n);
}

int	init_args(t_args *args, int argc, char **argv)
{
	int	*par;

	if (argc != 5 && argc != 6)
		return (ERR);
	if (argc == 5)
		args->nbr_tte = 0;
	args->stopped = 0;
	par = &args->nbr_phs;
	while (--argc > 0)
	{
		*par = parse_parameter(*argv++);
		if (*par++ < 0)
			return (ERR);
	}
	if (pthread_mutex_init(&args->mutex_speech, NULL) || args->nbr_phs < 1)
		return (ERR);
	return (OK);
}

t_fork	*create_forks(t_args *args)
{
	int				i;
	t_fork			*forks;

	forks = malloc(sizeof(t_fork) * args->nbr_phs);
	if (!forks)
		return (NULL);
	i = -1;
	while (++i < args->nbr_phs)
	{
		if (pthread_mutex_init(&forks[i].mutex, NULL))
		{
			while (i-- > 0)
				pthread_mutex_destroy(&forks[i].mutex);
			free(forks);
			return (NULL);
		}
		forks[i].last_id = 0;
	}
	return (forks);
}

int	prepare(t_fork **forks, t_args *args)
{
	struct timeval	tv;

	*forks = create_forks(args);
	if (!*forks)
		return (print_and_return(ERRMUTEX, ERR));
	if (gettimeofday(&tv, NULL) < 0)
		return (print_and_return(ERRTIME, ERR));
	set_timestamp(&tv, &args->ts);
	return (OK);
}
