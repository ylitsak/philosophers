/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:52:08 by saylital          #+#    #+#             */
/*   Updated: 2024/11/21 11:32:11 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assing_forks(t_lock_struct *l, int amount)
{
	int	i;

	i = 0;
	if (amount == 1)
	{
		l->philos[0].left_fork = &l->forks[0];
	//	l->philos[0].right_fork = NULL;
		l->philos[0].back = l;
		i++;
	}
	else
	{
		while (i < amount)
		{
			l->philos[i].left_fork = &l->forks[i];
			l->philos[i].right_fork = &l->forks[(i + 1) % amount];
			l->philos[i].back = l;
			i++;
		}
	}
}

int	init_mutex(t_lock_struct *l, int amount)
{
	int				i;

	i = 0;
	if (pthread_mutex_init(&l->print_lock, NULL) != 0)
	{
		printf("Mutex_init print_lock failed\n");
		free(l->philos);
		return (1);
	}
	if (pthread_mutex_init(&l->dead_lock, NULL) != 0)
	{
		printf("Mutex_init print_lock failed\n");
		free(l->philos);
		return (1);
	}
	l->forks = malloc(sizeof(pthread_mutex_t) * amount);
	if (!l->forks)
	{
		printf("Malloc failed making forks\n");
		free(l->philos);
		return (1);
	} 
	while (i < amount)
	{
		if (pthread_mutex_init(&l->forks[i], NULL) != 0)
		{
			printf("Mutex_init failed\n");
			free(l->forks);
			free(l->philos);
			return (1);
		}
		i++;
	}
	assing_forks(l, amount);
	return (0);
}
