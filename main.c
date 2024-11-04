/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:39:02 by saylital          #+#    #+#             */
/*   Updated: 2024/11/04 15:58:52 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//argv[1] = number of philos
//argv[2] = time it will take them to die
//argv[3] = time it will take them to eat
//argv[4] = time it will take them to sleep
//argv[5] = (optional) If all philosophers have eaten at least 
			//number_of_times_each_philosopher_must_eat times, 
			//the simulation stops. If not specified, the simulation stops
			//when a philosopher dies.
/*memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock*/
#include "philo.h"

void	*test(void *arg)
{
	(void)arg;
	printf("Hello\n");
	return (NULL);
}

int	create_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->n_philo)
	{
		if ((pthread_create(&philo[i].thread, NULL, &test, NULL)) != 0)
		{
			printf("Error creating threads\n");
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < philo->n_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
		{
			printf("Error joining threads\n");
			return (1);
		}
		i++;
	}
	return (0);
}
void	init_philos(t_philo *philo, int argc, char *argv[])
{
	philo->n_philo = ft_atoi_long(argv[1]);
	philo->time_die = ft_atoi_long(argv[2]);
	philo->time_eat = ft_atoi_long(argv[3]);
	philo->time_sleep = ft_atoi_long(argv[4]);
	if (argc == 6)
		philo->n_eaten = ft_atoi_long(argv[5]);
}

int	main(int argc, char *argv[])
{
	t_philo	philo;

	if (argc != 5 && argc != 6)
	{
		printf("Incorrect amount of arguments.\n");
		return (1);
	}
	if (check_input(&argv[1]) == 1)
	{
		printf("Incorrect input\n");
		return (1);
	}
	init_philos(&philo, argc, argv);
	//printf("%d %zu %zu %zu %d\n", philo.n_philo, philo.time_die, philo.time_eat, philo.time_sleep, philo.n_eaten);
	if (create_threads(&philo) != 0)
		return (1);
	return (0);
}