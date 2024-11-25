/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:36:45 by saylital          #+#    #+#             */
/*   Updated: 2024/11/25 14:01:26 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_lock_struct *monitor, int amount)
{
	pthread_t		death_monitor;
	int	i;

	i = 0;
	if (pthread_create(&death_monitor, NULL, &monitor_thread, monitor) != 0)
	{
		printf("Error creating thread\n");
		return (-1);
	}
	while (i < amount)
	{
		if ((pthread_create(&monitor->philos[i].thread, NULL, &routine, &monitor->philos[i])) != 0)
		{
			printf("Error creating threads\n");
			return (-1);
		}
		i++;
	}
	i = 0;
	if (pthread_join(death_monitor, NULL) != 0)
	{
		printf("Error joining threads\n");
		return (-1);
	}
	while (i < amount)
	{
		if (pthread_join(monitor->philos[i].thread, NULL) != 0)
		{
			printf("Error joining threads\n");
			return (-1);
		}
		i++;
	}
	return (0);
}
