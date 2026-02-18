/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemonthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 12:53:55 by jemonthi          #+#    #+#             */
/*   Updated: 2026/01/31 15:38:34 by jemonthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long	ft_atol(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	if (ft_strlen(str) > 11)
	{
		result = 214748364890;
		return (result);
	}
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result);
}

int	convert_to_long(char **argv)
{
	long	number;
	int		i;

	i = 1;
	while (argv[i] != NULL)
	{
		number = ft_atol(argv[i]);
		if (number <= 0 || number > INT_MAX)
		{
			write (2, "Error: number is zero or higher than INT_MAX\n", 45);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_argv(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i] != NULL)
	{
		j = 0;
		if (argv[i][j] == '+')
			j++;
		if (argv[i][j] == '\0')
			return (1);
		while (argv[i][j] != '\0')
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
