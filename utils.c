/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:29:27 by saylital          #+#    #+#             */
/*   Updated: 2024/11/25 14:25:30 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi_long(char *str)
{
	int		neg;
	long	num;

	neg = 1;
	num = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = (*str - '0') + num * 10;
		str++;
	}
	return (num * neg);
}

int	check_input(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 0;
	if (argc != 5 && argc != 6)
		return (-1);
	while (argv[i])
	{
		j = 0;
		if (argv[i][j] == '-' || argv[i][j] == '0')
		{
			return (-1);
		}
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	free_and_detroy(int amount, t_main_struct *monitor)
{
	int	i;

	i = 0;
	if (monitor->philos != NULL)
		free(monitor->philos);
	while (i < amount)
	{
		pthread_mutex_destroy(&monitor->forks[i]);
		i++;
	}
	if (monitor->forks != NULL)
		free(monitor->forks);
	return ;
}
