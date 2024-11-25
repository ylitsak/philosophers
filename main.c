/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:39:02 by saylital          #+#    #+#             */
/*   Updated: 2024/11/25 14:25:30 by saylital         ###   ########.fr       */
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
//printf("%d %zu %zu %zu %d\n", philo.n_philo, philo.time_die, philo.time_eat, philo.time_sleep, philo.n_eaten);

#include "philo.h"

void	init_philos(t_main_struct *monitor, int amount, int argc, char *argv[])
{
	int			i;
	long long	sim_start;

	i = 0;
	sim_start = start_time();
	while (i < amount)
	{
		monitor->philos[i].n_philo = ft_atoi_long(argv[1]);
		monitor->philos[i].die_time = ft_atoi_long(argv[2]);
		monitor->philos[i].eat_time = ft_atoi_long(argv[3]);
		monitor->philos[i].sleep_time = ft_atoi_long(argv[4]);
		monitor->philos[i].p_index = i + 1;
		monitor->philos[i].died = &monitor->is_dead;
		monitor->philos[i].start_time = sim_start;
		monitor->philos[i].last_meal = sim_start;
		if (argc == 6)
			monitor->philos[i].eaten = ft_atoi_long(argv[5]);
		else
			monitor->philos[i].eaten = -1;
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_main_struct	monitor;
	int				amount;

	monitor.is_dead = 0;
	if (check_input(argc, &argv[1]) != 0)
	{
		printf("Incorrect input\n");
		return (-1);
	}
	amount = ft_atoi_long(argv[1]);
	monitor.philos = malloc(amount * sizeof(t_philo));
	if (!monitor.philos)
	{
		printf("Malloc failed\n");
		return (-1);
	}
	init_philos(&monitor, amount, argc, argv);
	if (init_mutex(&monitor, amount) != 0)
		return (-1);
	if (create_threads(&monitor, amount) != 0)
		return (-1);
	free_and_detroy(amount, &monitor);
	return (0);
}
