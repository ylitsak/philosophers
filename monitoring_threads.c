/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:45:39 by saylital          #+#    #+#             */
/*   Updated: 2024/11/25 14:04:28 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_philo *p)
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

static void	one_philo(t_philo *p)
{
		pthread_mutex_lock(p->left_fork);
		print_message(p, "has taken a fork");
		usleep(p->die_time * 1000);
		pthread_mutex_unlock(p->left_fork);
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

void	*monitor_thread(void *arg)
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
