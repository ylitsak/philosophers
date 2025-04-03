/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:39:02 by saylital          #+#    #+#             */
/*   Updated: 2025/04/03 13:24:09 by saylital         ###   ########.fr       */
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
//printf("%d %zu %zu %zu %d\n", philo.n_philo, philo.time_die, philo.time_eat,
// philo.time_sleep, philo.n_eaten);

#include "philo.h"

static void	init_philos(t_main_struct *m, int amount, int argc, char **argv)
{
	int			i;
	long long	sim_start;

	i = 0;
	m->is_dead = 0;
	sim_start = start_time();
	while (i < amount)
	{
		m->philos[i].n_philo = ft_atoi_long(argv[1]);
		m->philos[i].die_time = ft_atoi_long(argv[2]);
		m->philos[i].eat_time = ft_atoi_long(argv[3]);
		m->philos[i].sleep_time = ft_atoi_long(argv[4]);
		m->philos[i].p_index = i + 1;
		m->philos[i].died = &m->is_dead;
		m->philos[i].start_time = sim_start;
		m->philos[i].last_meal = sim_start;
		if (argc == 6)
			m->philos[i].eaten = ft_atoi_long(argv[5]);
		else
			m->philos[i].eaten = -1;
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_main_struct	monitor;
	int				amount;

	if (check_input(argc, &argv[1]) != 0)
	{
		print_error("Incorrect input", 2);
		return (-1);
	}
	amount = ft_atoi_long(argv[1]);
	monitor.philos = malloc(amount * sizeof(t_philo));
	if (!monitor.philos)
	{
		print_error("Malloc failed", 2);
		return (-1);
	}
	init_philos(&monitor, amount, argc, argv);
	if (init_mutex(&monitor, amount) != 0)
		return (-1);
	if (create_threads(&monitor, amount) != 0)
	{
		free_and_destroy(amount, &monitor);
		return (-1);
	}
	free_and_destroy(amount, &monitor);
	return (0);
}
