/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_and_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemonthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 19:11:40 by jemonthi          #+#    #+#             */
/*   Updated: 2026/03/03 19:41:36 by jemonthi         ###   ########.fr       */
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

int	one_philo_only(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->rules->print_mutex);
	printf("%ld %d has taken a fork\n",
		get_time_ms() - philo->rules->start_time, philo->id);
	pthread_mutex_unlock(&philo->rules->print_mutex);
	usleep(philo->rules->time_to_die * 1000L);
	pthread_mutex_unlock(philo->left_fork);
	return (1);
}

int	is_stopped(t_rules *rules)
{
	int	ret;

	pthread_mutex_lock(&rules->lock_stop);
	ret = rules->stop;
	pthread_mutex_unlock(&rules->lock_stop);
	return (ret);
}
