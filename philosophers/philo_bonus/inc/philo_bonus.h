/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 13:13:35 by dgidget           #+#    #+#             */
/*   Updated: 2021/08/25 11:50:30 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define ERRARG 		"Incorrect arguments"

# define OK		0
# define ERR	-1

# define COLOR_RED		"\x1b[31m"
# define COLOR_GREEN	"\x1b[32m"
# define COLOR_YELLOW	"\x1b[33m"
# define COLOR_CYAN		"\x1b[36m"
# define COLOR_KMAG		"\x1B[35m"
# define COLOR_RESET	"\x1b[0m"

# define EATING			"is eating"
# define SLEEPING		"is sleeping"
# define THINKING		"is thinking"
# define DIED			"has died"
# define FORK			"has taken a fork"

# define SEM_NAME		"philo_sem"
# define TABLE_NAME		"table"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <pthread.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct s_args
{
	int			nbr_phs;
	int			ttd;
	int			tte;
	int			tts;
	int			nbr_tte;
	long long	ts;
	int			stopped;
	pid_t		*pids;
	char		*table_name;
	sem_t		*sem_table;
	char		*forks_name;
	sem_t		*sem_forks;
}	t_args;

typedef struct s_philo
{
	int			id;
	t_args		*args;
	int			meals;
	long long	last_meal;
	
}	t_philo;

int			init_args(t_args *args, int argc, char **argv);
int			error(char *s, int code);
long long	set_timestamp(struct timeval *tv, long long *ts);
void		routine(t_philo *philo);
void		msleep(long long start, int msecs);
void		print_state(char *msg, char *color, t_philo *philo);
void		declare_death(t_philo *philo);
int			is_alive(t_philo *philo);

void		free_all(void *pids);

#endif
