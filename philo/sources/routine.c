/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemonthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 19:11:40 by jemonthi          #+#    #+#             */
/*   Updated: 2026/02/16 23:16:22 by jemonthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000));
}

int	print_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->rules->print_mutex);
	if (is_stopped(philo->rules))
	{
		pthread_mutex_unlock(&philo->rules->print_mutex);
		return (1);
	}
	printf("%ld %d %s\n", get_time_ms() - philo->rules->start_time,
		philo->id, msg);
	pthread_mutex_unlock(&philo->rules->print_mutex);
	return (0);
}

int	check_nbr_philo(t_philo *philo)
{
	if (philo->rules->nbr_philo == 1)
	{
		usleep(philo->rules->time_to_die * 1000L);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	if (print_msg(philo, "has taken a fork"))
	{
		if (philo->id % 2 == 0)
			pthread_mutex_unlock(philo->right_fork);
		else
			pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	if (check_nbr_philo(philo))
		return (1);
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->left_fork);
	else
		pthread_mutex_lock(philo->right_fork);
	if (print_msg(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	return (0);
}

int	is_stopped(t_rules *rules)
{
	int	ret;

	pthread_mutex_lock(&rules->lock_stop);
	ret = rules->stop;
	pthread_mutex_unlock(&rules->lock_stop);
	return (ret);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = data;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_stopped(philo->rules))
	{
		if (print_msg(philo, "is thinking"))
			break ;
		if (take_forks(philo))
			break ;
		pthread_mutex_lock(&philo[0].rules->lock_last_meal);
		philo->last_meal = get_time_ms();
		pthread_mutex_unlock(&philo[0].rules->lock_last_meal);
		if (print_msg(philo, "is eating"))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}
		pthread_mutex_lock(&philo[0].rules->lock_meals_eaten);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo[0].rules->lock_meals_eaten);
		usleep(philo->rules->time_to_eat * 1000L);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (print_msg(philo, "is sleeping"))
			break ;
		usleep(philo->rules->time_to_sleep * 1000L);
	}
	return (NULL);
}
