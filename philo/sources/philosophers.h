/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemonthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 12:53:55 by jemonthi          #+#    #+#             */
/*   Updated: 2026/01/31 15:38:34 by jemonthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_rules
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	pthread_mutex_t	*forks;
	int				stop;
	long			start_time;
	pthread_mutex_t	print_mutex;
}	t_rules;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	t_rules			*rules;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

/* parsing and utilities functions */

int		check_argv(char **argv);
size_t	ft_strlen(char *str);
long	ft_atol(char *str);
int		convert_to_long(char **argv);

/* creation and initiation of philo and forks */

void	init_forks(t_rules *info);
void	init_philo(t_rules *info, t_philo *philo);
void	create_thread_philo(t_rules *info, t_philo *philo);
void	join_thread_philo(t_rules *info, t_philo *philo);

/* fill the list */

void	get_into_list(int argc, char **argv);
void	*monitor(void *data);
void	*routine(void *data);
long	get_time_ms(void);
int		check_done(t_philo *philo, int done);
int		check_dead(t_philo *philo, int i);

/* free and destroys mutex */

void	destroy_all(t_rules *info);

#endif
