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
	if (philo->rules->stop)
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

void	*routine(void *data)
{
	t_philo	*philo;

	philo = data;
	while (!philo->rules->stop)
	{
		if (print_msg(philo, "is thinking"))
			break ;
		if (take_forks(philo))
			break ;
		philo->last_meal = get_time_ms();
		if (print_msg(philo, "is eating"))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}
		philo->meals_eaten++;
		usleep(philo->rules->time_to_eat * 1000L);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (print_msg(philo, "is sleeping"))
			break ;
		usleep(philo->rules->time_to_sleep * 1000L);
	}
	return (NULL);
}
