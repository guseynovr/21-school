/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 12:46:14 by dgidget           #+#    #+#             */
/*   Updated: 2021/08/20 13:33:12 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define OK		0
# define ERR	1

# define ERRARG 		"Incorrect arguments\n"
# define ERRTIME		"Error getting time of day\n"
# define ERRMUTEX		"Error while creating mutexex\n"
# define ERRTHREAD		"Error while creating threads\n"

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

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_args
{
	int				nbr_phs;
	int				ttd;
	int				tte;
	int				tts;
	int				nbr_tte;
	long long		ts;
	int				stopped;
	pthread_mutex_t	mutex_speech;
}	t_args;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				last_id;
}	t_fork;

typedef struct s_philo
{
	int				id;
	t_fork			*left;
	t_fork			*right;
	t_args			*args;
	int				meals;
	long long		last_meal;
}	t_philo;

int			init_args(t_args *args, int argc, char **argv);
int			prepare(t_fork **forks, t_args *args);
int			print_and_return(char *msg, int ret);
long long	set_timestamp(struct timeval *tv, long long *ts);

pthread_t	*create_philos(t_args *args, t_fork *forks,
				t_philo **philos);
void		*routine(void *data);
void		msleep(long long start, int msecs);

void		print_state(char *msg, char *color, t_philo *philo);
void		declare_death(t_philo *philo);
int			is_alive(t_philo *philo);
void		declare_death(t_philo *philo);
void		join_philos(pthread_t *philos, t_args *args, pthread_t monitor);

void		free_all(void *p1, void *p2, void *p3, pthread_mutex_t *mutex);

#endif
