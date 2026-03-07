/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemonthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 12:53:55 by jemonthi          #+#    #+#             */
/*   Updated: 2026/01/31 15:38:34 by jemonthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_into_list(int argc, char **argv)
{
	t_rules		*info;
	t_philo		*philo;

	info = malloc(sizeof(t_rules));
	if (!info)
	{
		write (2, "Error: Malloc of info has failed\n", 33);
		return ;
	}
	if (fill_info(argc, argv, info))
		return ;
	philo = malloc(sizeof(t_philo) * info->nbr_philo);
	if (!philo)
	{
		write (2, "Error: Malloc of philo has failed\n", 34);
		free (info->forks);
		free (info);
		return ;
	}
	simulate_threads(info, philo);
}

int	fill_info(int argc, char **argv, t_rules *info)
{
	info->nbr_philo = ft_atol(argv[1]);
	info->time_to_die = ft_atol(argv[2]);
	info->time_to_eat = ft_atol(argv[3]);
	info->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		info->must_eat = ft_atol(argv[5]);
	else
		info->must_eat = -1;
	info->start_time = get_time_ms();
	info->stop = 0;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->nbr_philo);
	if (!info->forks)
	{
		write (2, "Error: Malloc of forks has failed\n", 34);
		free (info);
		return (1);
	}
	return (0);
}

void	simulate_threads(t_rules *info, t_philo *philo)
{
	pthread_t	data;

	init_forks(info);
	init_philo(info, philo);
	create_thread_philo(info, philo);
	pthread_create(&data, NULL, monitor, philo);
	join_thread_philo(info, philo);
	pthread_join(data, NULL);
	destroy_all(info, philo);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		write(2, "Error: Wrong number of arguments\n", 33);
		return (1);
	}
	if (check_argv(argv) == 0)
	{
		if (convert_to_long(argv) == 0)
		{
			get_into_list(argc, argv);
		}
		else
			return (1);
	}
	else
	{
		write (2, "Error: Please write only positive number in argument\n", 53);
		return (1);
	}
	return (0);
}
