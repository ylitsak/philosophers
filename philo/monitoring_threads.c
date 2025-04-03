/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:45:39 by saylital          #+#    #+#             */
/*   Updated: 2025/04/03 19:41:13 by saylital         ###   ########.fr       */
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
	wait_in_ms(p, p->die_time);
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
	philo_thinking(p, 0);
	if (p->p_index % 2 == 0)
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
		philo_actions(p);
		usleep(100);
	}
	return (NULL);
}

static int	philos_status_loop(t_main_struct *m)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < m->philos->n_philo)
	{
		pthread_mutex_lock(&m->value_lock);
		if (m->philos[i].eaten == 0)
			count++;
		pthread_mutex_unlock(&m->value_lock);
		if (check_death(&m->philos[i]) != 0)
			return (0);
		i++;
	}
	if (count == m->philos->n_philo)
	{
		pthread_mutex_lock(&m->dead_lock);
		m->is_dead = 1;
		pthread_mutex_unlock(&m->dead_lock);
		return (0);
	}
	usleep(100);
	return (1);
}

void	*monitor_thread(void *arg)
{
	t_main_struct	*main_monitor;

	main_monitor = (t_main_struct *)arg;
	while (1)
	{
		if (philos_status_loop(main_monitor) == 0)
			return (NULL);
	}
	return (NULL);
}
