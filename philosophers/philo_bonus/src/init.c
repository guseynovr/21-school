/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 13:37:13 by dgidget           #+#    #+#             */
/*   Updated: 2021/08/25 11:57:14 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	parse_parameter(char *s)
{
	int	n;

	n = 0;
	while (*s && *s >= '0' && *s <= '9')
		n = n * 10 + *s++ - '0';
	if (*s && (*s < '0' || *s > '9'))
		return (ERR);
	return (n);
}

int	init_args(t_args *args, int argc, char **argv)
{
	struct timeval	tv;
	int				*par;

	if (argc != 5 && argc != 6)
		return (error(ERRARG, ERR));
	if (argc == 5)
		args->nbr_tte = 0;
	args->stopped = 0;
	par = &args->nbr_phs;
	while (--argc > 0)
	{
		*par = parse_parameter(*argv++);
		if (*par++ < 0)
			return (error(ERRARG, ERR));
	}
	args->table_name = TABLE_NAME;
	args->sem_table = sem_open(args->table_name, O_CREAT, 777, 1);
	sem_post(args->sem_table);
	args->forks_name = SEM_NAME;
	args->sem_forks = sem_open(args->forks_name, O_CREAT, 777, args->nbr_phs);
	int i = -1;
	while (++i < args->nbr_phs)
		sem_post(args->sem_forks);
	gettimeofday(&tv, NULL);
	set_timestamp(&tv, &args->ts);
	// printf("%u\n", (unsigned int) args->nbr_phs);
	return (OK);
}
