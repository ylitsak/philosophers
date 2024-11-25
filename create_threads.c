/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:36:45 by saylital          #+#    #+#             */
/*   Updated: 2024/11/25 14:58:41 by saylital         ###   ########.fr       */
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

	i = 0;
	while (i < amount)
	{
		if ((pthread_create(&monitor->philos[i].thread, NULL, &routine, &monitor->philos[i])) != 0)
		{
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
		printf("Error creating thread\n");
		return (-1);
	}
	if (create_philo_threads(monitor, amount) != 0)
	{
		printf("Error creating philo threads\n");
		return (-1);
	}
	if (pthread_join(main_monitor, NULL) != 0)
	{
		printf("Error joining threads\n");
		return (-1);
	}
	if (join_philo_threads(monitor, amount) != 0)
	{
		printf("Error joining philo threads\n");
		return (-1);
	}
	return (0);
}
