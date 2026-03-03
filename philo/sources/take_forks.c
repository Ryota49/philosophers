/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemonthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 19:40:30 by jemonthi          #+#    #+#             */
/*   Updated: 2026/03/03 19:45:23 by jemonthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	inpair_id(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (is_stopped(philo->rules))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->rules->print_mutex);
	printf("%ld %d has taken a fork\n",
		get_time_ms() - philo->rules->start_time, philo->id);
	pthread_mutex_unlock(&philo->rules->print_mutex);
	pthread_mutex_lock(philo->right_fork);
	if (is_stopped(philo->rules))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->rules->print_mutex);
	printf("%ld %d has taken a fork\n",
		get_time_ms() - philo->rules->start_time, philo->id);
	pthread_mutex_unlock(&philo->rules->print_mutex);
	return (0);
}

int	pair_id(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (is_stopped(philo->rules))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->rules->print_mutex);
	printf("%ld %d has taken a fork\n",
		get_time_ms() - philo->rules->start_time, philo->id);
	pthread_mutex_unlock(&philo->rules->print_mutex);
	pthread_mutex_lock(philo->left_fork);
	if (is_stopped(philo->rules))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->rules->print_mutex);
	printf("%ld %d has taken a fork\n",
		get_time_ms() - philo->rules->start_time, philo->id);
	pthread_mutex_unlock(&philo->rules->print_mutex);
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->rules->nbr_philo == 1)
	{
		one_philo_only(philo);
		return (1);
	}
	if (philo->id % 2 == 0)
	{
		if (pair_id(philo))
			return (1);
	}
	else
	{
		if (inpair_id(philo))
			return (1);
	}
	pthread_mutex_lock(&philo->rules->lock_last_meal);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->rules->lock_last_meal);
	return (0);
}
