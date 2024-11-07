/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:39:02 by saylital          #+#    #+#             */
/*   Updated: 2024/11/07 14:18:04 by saylital         ###   ########.fr       */
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
	pthread_mutex_lock(p->left_fork);
	pthread_mutex_lock(p->right_fork);
	usleep(2000000);
	printf("Hello\n");
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	return (NULL);
}

int	create_threads(t_lock_struct *l, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		if ((pthread_create(&l->philos[i].thread, NULL, &routine, (void *)&l->philos[i])) != 0)
		{
			printf("Error creating threads\n");
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < amount)
	{
		if (pthread_join(l->philos[i].thread, NULL) != 0)
		{
			printf("Error joining threads\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	init_philos(t_lock_struct *l, int amount, int argc, char *argv[])
{
	int	i;

	i = 0;
	while (i < amount)
	{
		l->philos[i].n_philo = ft_atoi_long(argv[1]);
		l->philos[i].time_die = ft_atoi_long(argv[2]);
		l->philos[i].time_eat = ft_atoi_long(argv[3]);
		l->philos[i].time_sleep = ft_atoi_long(argv[4]);
		if (argc == 6)
			l->philos[i].n_eaten = ft_atoi_long(argv[5]);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_lock_struct	l;
	int		amount;
	int		i;

	i = 0;
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
	l.philos = malloc(amount * sizeof(t_philo));
	if (!l.philos)
	{
		printf("Malloc failed\n");
		return (1);
	}
	init_philos(&l, amount, argc, argv);
	if (init_mutex(&l, amount) != 0)
		return (1);
	if (create_threads(&l, amount) != 0)
		return (1);
	while (i < amount)
	{
		pthread_mutex_destroy(&(l.forks[i]));
		i++;
	}
	free(l.philos);
	free(l.forks);
	return (0);
}
