/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:36:45 by saylital          #+#    #+#             */
/*   Updated: 2024/11/26 13:23:19 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	join_philo_threads(t_main_struct *monitor, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		if (pthread_join(monitor->philos[i].thread, NULL) != 0)
		{
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	create_philo_threads(t_main_struct *monitor, int amount)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < amount)
	{
		if ((pthread_create(&monitor->philos[i].thread, NULL, &routine, &monitor->philos[i])) != 0)
		{
			while (j < i)
			{
				if (pthread_join(monitor->philos[j].thread, NULL) != 0)
				{
					print_error("Error joining philos while cleanup", 2);
					return (-1);
				}
				j++;
			}
			return (-1);
		}
		i++;
	}
	return (0);
}

int	create_threads(t_main_struct *monitor, int amount)
{
	pthread_t		main_monitor;

	if (pthread_create(&main_monitor, NULL, &monitor_thread, monitor) != 0)
	{
		print_error("Error creating main thread", 2);
		return (-1);
	}
	if (create_philo_threads(monitor, amount) != 0)
	{
		if (pthread_join(main_monitor, NULL) != 0)
			print_error("Error joining main thread while cleanup", 2);
		print_error("Error creating philo threads", 2);
		return (-1);
	}
	if (pthread_join(main_monitor, NULL) != 0)
	{
		print_error("Error joining main thread", 2);
		return (-1);
	}
	if (join_philo_threads(monitor, amount) != 0)
	{
		print_error("Error joining philo threads", 2);
		return (-1);
	}
	return (0);
}
