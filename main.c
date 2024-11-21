/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:39:02 by saylital          #+#    #+#             */
/*   Updated: 2024/11/21 15:09:24 by saylital         ###   ########.fr       */
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

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->n_philo == 1)
	{
		pthread_mutex_lock(p->left_fork);
		printf("%lld %d has taken a fork\n",elapsed_time(p), p->p_index);
		usleep(p->die_time * 1000);
		pthread_mutex_unlock(p->left_fork);
		return (NULL);
	}
	if (p->p_index % 2 == 1)
	{
		philo_thinking(p);
		usleep(200);
	}
	while (1)
	{
		pthread_mutex_lock(&p->back->dead_lock);
		if (p->died[0] == 1)
		{
			pthread_mutex_unlock(&p->back->dead_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&p->back->dead_lock);
		philo_eating(p);
		philo_sleeping(p);
		philo_thinking(p);
	}
	return (NULL);
}

int check_death(t_philo *p)
{
	pthread_mutex_lock(&p->back->dead_lock);
	if ((start_time() - p->last_meal) > p->die_time)
	{
		p->died[0] = 1;
		pthread_mutex_unlock(&p->back->dead_lock);
		pthread_mutex_lock(&p->back->print_lock);
		printf("%lld %d died\n", elapsed_time(p), p->p_index);
		pthread_mutex_unlock(&p->back->print_lock);
		return (1);
	}
	pthread_mutex_unlock(&p->back->dead_lock);
	return (0);
}
void	*is_philo_alive(void *arg)
{
	t_lock_struct	*death_track;
	int				i;
	int				count;

	death_track = (t_lock_struct *)arg;
	while (1)
	{
		i = 0;
		count = 0;
		while (i < death_track->philos->n_philo)
		{
			if (death_track->philos[i].eaten == 0)
				count++;
			if (check_death(&death_track->philos[i]))
				return (NULL);
			i++;
		}
		if (count == death_track->philos->n_philo)
		{
			death_track->is_dead = 1;
			return (NULL);
		}
	}
	return (NULL);
}

int	create_threads(t_lock_struct *monitor, int amount)
{
	pthread_t		death_monitor;
	int	i;

	i = 0;
	if (pthread_create(&death_monitor, NULL, &is_philo_alive, monitor) != 0)
	{
		printf("Error creating thread\n");
		return (1);
	}
	while (i < amount)
	{
		if ((pthread_create(&monitor->philos[i].thread, NULL, &routine, (void *)&monitor->philos[i])) != 0)
		{
			printf("Error creating threads\n");
			return (1);
		}
		i++;
	}
	i = 0;
	if (pthread_join(death_monitor, NULL) != 0)
	{
		printf("Error joining threads\n");
		return (1);
	}
	while (i < amount)
	{
		if (pthread_join(monitor->philos[i].thread, NULL) != 0)
		{
			printf("Error joining threads\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	init_philos(t_lock_struct *monitor, int amount, int argc, char *argv[])
{
	int	i;
	long long sim_start;

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
	t_lock_struct	monitor;
	int		amount;
	int		i;

	i = 0;
	monitor.is_dead = 0;
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
	amount = ft_atoi_long(argv[1]);
	monitor.philos = malloc(amount * sizeof(t_philo));
	if (!monitor.philos)
	{
		printf("Malloc failed\n");
		return (1);
	}
	init_philos(&monitor, amount, argc, argv);
	if (init_mutex(&monitor, amount) != 0)
		return (1);
	if (create_threads(&monitor, amount) != 0)
		return (1);
	while (i < amount)
	{
		pthread_mutex_destroy(&(monitor.forks[i]));
		i++;
	}
	free(monitor.philos);
	free(monitor.forks);
	return (0);
}
