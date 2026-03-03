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

void	fixed_sleep(unsigned long n, t_rules *rules)
{
	unsigned long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < n)
	{
		if (is_stopped(rules))
			return ;
		usleep(200);
	}
}

int	sleep_thread(t_philo *philo)
{
	long	time;

	if (print_msg(philo, "is sleeping"))
		return (1);
	fixed_sleep(philo->rules->time_to_sleep, philo->rules);
	if (philo->rules->nbr_philo % 2 != 0)
	{
		time = philo->rules->time_to_eat * 2 - philo->rules->time_to_sleep;
		if (time < 0)
			time = 0;
		if (time > 0)
			fixed_sleep((unsigned long)time, philo->rules);
	}
	return (0);
}

int	eat_thread(t_philo *philo)
{
	if (print_msg(philo, "is eating"))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->rules->lock_meals_eaten);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->rules->lock_meals_eaten);
	fixed_sleep(philo->rules->time_to_eat, philo->rules);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = data;
	if (philo->id % 2 == 0)
		fixed_sleep(philo->rules->time_to_eat, philo->rules);
	while (!is_stopped(philo->rules))
	{
		if (print_msg(philo, "is thinking"))
			break ;
		if (take_forks(philo))
			break ;
		if (eat_thread(philo))
			break ;
		if (sleep_thread(philo))
			break ;
	}
	return (NULL);
}
