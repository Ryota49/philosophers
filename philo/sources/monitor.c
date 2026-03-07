/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemonthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 19:11:40 by jemonthi          #+#    #+#             */
/*   Updated: 2026/03/03 19:41:36 by jemonthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor(void *data)
{
	t_philo	*philo;
	int		i;
	int		done;

	philo = data;
	while (!is_stopped(philo->rules))
	{
		i = 0;
		done = 0;
		while (i < philo[0].rules->nbr_philo)
		{
			if (check_dead(philo, i))
				return (NULL);
			pthread_mutex_lock(&philo[0].rules->lock_meals_eaten);
			if (philo[i].meals_eaten >= philo[i].rules->must_eat
				&& philo[0].rules->must_eat != -1)
				done++;
			pthread_mutex_unlock(&philo[0].rules->lock_meals_eaten);
			i++;
		}
		if (check_done(philo, done))
			break ;
		usleep(1000);
	}
	return (NULL);
}

int	check_dead(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo[0].rules->lock_last_meal);
	if ((get_time_ms() - philo[i].last_meal) > philo[i].rules->time_to_die)
	{
		pthread_mutex_unlock(&philo[0].rules->lock_last_meal);
		pthread_mutex_lock(&philo[0].rules->lock_stop);
		philo[0].rules->stop = 1;
		pthread_mutex_unlock(&philo[0].rules->lock_stop);
		pthread_mutex_lock(&philo[0].rules->print_mutex);
		printf("%ld %d died\n",
			get_time_ms() - philo[i].rules->start_time, philo[i].id);
		pthread_mutex_unlock(&philo[0].rules->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo[0].rules->lock_last_meal);
	return (0);
}

int	check_done(t_philo *philo, int done)
{
	if (done == philo[0].rules->nbr_philo)
	{
		pthread_mutex_lock(&philo[0].rules->lock_stop);
		philo[0].rules->stop = 1;
		pthread_mutex_unlock(&philo[0].rules->lock_stop);
		return (1);
	}
	return (0);
}
