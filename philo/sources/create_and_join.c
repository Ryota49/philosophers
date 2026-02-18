/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_join.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemonthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:41:55 by jemonthi          #+#    #+#             */
/*   Updated: 2026/02/16 22:42:34 by jemonthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_forks(t_rules *info)
{
	int	i;

	i = 0;
	pthread_mutex_init(&info->print_mutex, NULL);
	while (i < info->nbr_philo)
	{
		pthread_mutex_init(&info->forks[i], NULL);
		i++;
	}
}

void	init_philo(t_rules *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info->nbr_philo)
	{
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].rules = info;
		philo[i].left_fork = &info->forks[i];
		philo[i].right_fork = &info->forks[(i + 1) % info->nbr_philo];
		philo[i].last_meal = info->start_time;
		i++;
	}
	philo[0].rules->stop = 0;
}

void	create_thread_philo(t_rules *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info->nbr_philo)
	{
		pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
		i++;
	}
}

void	join_thread_philo(t_rules *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info->nbr_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

void	destroy_all(t_rules *info)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&info->print_mutex);
	while (i < info->nbr_philo)
	{
		pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
}
