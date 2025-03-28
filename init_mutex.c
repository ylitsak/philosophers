/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:52:08 by saylital          #+#    #+#             */
/*   Updated: 2025/03/27 14:52:03 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(t_main_struct *m, int amount)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < amount)
	{
		if (pthread_mutex_init(&m->forks[i], NULL) != 0)
		{
			while (j < i)
			{
				pthread_mutex_destroy(&m->forks[j]);
				j++;
			}
			print_error("Mutex_init_forks failed", 2);
			free(m->forks);
			free(m->philos);
			return (-1);
		}
		i++;
	}
	return (0);
}

static void	assign_forks(t_main_struct *m, int amount)
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
			if (i == amount - 1)
				m->philos[i].right_fork = &m->forks[0];
			else
				m->philos[i].right_fork = &m->forks[i + 1];
			m->philos[i].back = m;
			i++;
		}
	}
}

static void	mutex_failed(t_main_struct *m, char *msg)
{
	print_error(msg, 2);
	free(m->philos);
}

int	init_mutex(t_main_struct *m, int amount)
{
	if (pthread_mutex_init(&m->print_lock, NULL) != 0)
	{
		mutex_failed(m, "Mutex_init print_lock failed");
		return (-1);
	}
	if (pthread_mutex_init(&m->dead_lock, NULL) != 0)
	{
		mutex_failed(m, "Mutex_init dead_lock failed");
		return (-1);
	}
	if (pthread_mutex_init(&m->value_lock, NULL) != 0)
	{
		mutex_failed(m, "Mutex_init value_lock failed");
		return (-1);
	}
	m->forks = malloc(sizeof(pthread_mutex_t) * amount);
	if (!m->forks)
	{
		mutex_failed(m, "Malloc failed making forks");
		return (-1);
	}
	if (init_forks(m, amount) != 0)
		return (-1);
	assign_forks(m, amount);
	return (0);
}
