/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:45:39 by saylital          #+#    #+#             */
/*   Updated: 2025/03/24 14:26:28 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_philo *p)
{
	pthread_mutex_lock(&p->back->dead_lock);
	pthread_mutex_lock(&p->back->value_lock);
	if ((start_time() - p->last_meal) > p->die_time)
	{
		p->died[0] = 1;
		pthread_mutex_unlock(&p->back->value_lock);
		pthread_mutex_unlock(&p->back->dead_lock);
		pthread_mutex_lock(&p->back->print_lock);
		printf("%lld %d died\n", elapsed_time(p), p->p_index);
		pthread_mutex_unlock(&p->back->print_lock);
		return (-1);
	}
	pthread_mutex_unlock(&p->back->value_lock);
	pthread_mutex_unlock(&p->back->dead_lock);
	return (0);
}

static void	one_philo(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	print_message(p, "has taken a fork");
	usleep(p->die_time * 1000);
	pthread_mutex_unlock(p->left_fork);
}

static void	sync_routine(t_philo *p)
{
	philo_thinking(p);
	usleep(200);
	return ;
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->n_philo == 1)
	{
		one_philo(p);
		return (NULL);
	}
	if (p->p_index % 2 == 1)
		sync_routine(p);
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
		usleep(100);
	}
	return (NULL);
}

void	*monitor_thread(void *arg)
{
	t_main_struct	*main_monitor;
	int				i;
	int				count;

	main_monitor = (t_main_struct *)arg;
	while (1)
	{
		i = 0;
		count = 0;
		while (i < main_monitor->philos->n_philo)
		{
			if (main_monitor->philos[i].eaten == 0)
				count++;
			if (check_death(&main_monitor->philos[i]) != 0)
				return (NULL);
			i++;
		}
		if (count == main_monitor->philos->n_philo)
		{
			main_monitor->is_dead = 1;
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
