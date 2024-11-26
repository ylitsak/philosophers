/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:52:08 by saylital          #+#    #+#             */
/*   Updated: 2024/11/26 12:39:27 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(t_main_struct *m, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		if (pthread_mutex_init(&m->forks[i], NULL) != 0)
		{
			print_error("Mutex_init failed", 2);
			free(m->forks);
			free(m->philos);
			return (-1);
		}
		i++;
	}
	return (0);
}

static void	assing_forks(t_main_struct *m, int amount)
{
	int	i;

	i = 0;
	if (amount == 1)
	{
		m->philos[0].left_fork = &m->forks[0];
		m->philos[0].right_fork = NULL;
		m->philos[0].back = m;
		i++;
	}
	else
	{
		while (i < amount)
		{
			m->philos[i].left_fork = &m->forks[i];
			m->philos[i].right_fork = &m->forks[(i + 1) % amount];
			m->philos[i].back = m;
			i++;
		}
	}
}

int	init_mutex(t_main_struct *m, int amount)
{
	if (pthread_mutex_init(&m->print_lock, NULL) != 0)
	{
		print_error("Mutex_init print_lock failed", 2);
		free(m->philos);
		return (-1);
	}
	if (pthread_mutex_init(&m->dead_lock, NULL) != 0)
	{
		print_error("Mutex_init dead_lock failed", 2);
		free(m->philos);
		return (-1);
	}
	m->forks = malloc(sizeof(pthread_mutex_t) * amount);
	if (!m->forks)
	{
		print_error("Malloc failed making forks", 2);
		free(m->philos);
		return (-1);
	}
	init_forks(m, amount);
	assing_forks(m, amount);
	return (0);
}
