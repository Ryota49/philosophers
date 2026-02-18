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

void	*monitor(void *data)
{
	t_philo	*philo;
	int		i;
	int		done;

	philo = data;
	while (philo[0].rules->stop == 0)
	{
		i = 0;
		done = 0;
		while (i < philo[0].rules->nbr_philo)
		{
			if (check_dead(philo, i))
				return (NULL);
			if (philo[i].meals_eaten >= philo[i].rules->must_eat
				&& philo[0].rules->must_eat != -1)
				done++;
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
	if (get_time_ms() - philo[i].last_meal > philo[i].rules->time_to_die)
	{
		pthread_mutex_lock(&philo[0].rules->print_mutex);
		printf("%ld %d died\n",
			get_time_ms() - philo[i].rules->start_time, philo[i].id);
		philo[0].rules->stop = 1;
		pthread_mutex_unlock(&philo[0].rules->print_mutex);
		return (1);
	}
	return (0);
}

int	check_done(t_philo *philo, int done)
{
	if (done == philo[0].rules->nbr_philo)
	{
		pthread_mutex_lock(&philo[0].rules->print_mutex);
		philo[0].rules->stop = 1;
		pthread_mutex_unlock(&philo[0].rules->print_mutex);
		return (1);
	}
	return (0);
}

void	get_into_list(int argc, char **argv)
{
	t_rules		info;
	t_philo		*philo;
	pthread_t	data;

	info.nbr_philo = ft_atol(argv[1]);
	info.time_to_die = ft_atol(argv[2]);
	info.time_to_eat = ft_atol(argv[3]);
	info.time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		info.must_eat = ft_atol(argv[5]);
	else
		info.must_eat = -1;
	info.start_time = get_time_ms();
	info.stop = 0;
	info.forks = malloc(sizeof(pthread_mutex_t) * info.nbr_philo);
	philo = malloc(sizeof(t_philo) * info.nbr_philo);
	init_forks(&info);
	init_philo(&info, philo);
	create_thread_philo(&info, philo);
	pthread_create(&data, NULL, monitor, philo);
	join_thread_philo(&info, philo);
	pthread_join(data, NULL);
	destroy_all(&info);
	free (philo);
	free (info.forks);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		write(2, "Error: wrong number of arguments\n", 33);
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
