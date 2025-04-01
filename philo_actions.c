/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:03:56 by saylital          #+#    #+#             */
/*   Updated: 2025/04/01 10:07:39 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eat(t_philo *p)
{
	print_message(p, "is eating");
	pthread_mutex_lock(&p->back->value_lock);
	if (p->eaten > 0)
		p->eaten--;
	p->last_meal = start_time();
	pthread_mutex_unlock(&p->back->value_lock);
	wait_in_ms(p, p->eat_time);
}

static void	philo_eating(t_philo *p)
{
	if (p->p_index % 2 == 0)
	{
		pthread_mutex_lock(p->right_fork);
		print_message(p, "has taken a fork");
		pthread_mutex_lock(p->left_fork);
		print_message(p, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(p->left_fork);
		print_message(p, "has taken a fork");
		pthread_mutex_lock(p->right_fork);
		print_message(p, "has taken a fork");
	}
	philo_eat(p);
	if (p->p_index % 2 != 0)
	{
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
	}
	else
	{
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(p->left_fork);
	}
}

void	philo_thinking(t_philo *p, int check)
{
	print_message(p, "is thinking");
	if (check == 1 && p->p_index % 2 != 0)
	{
		pthread_mutex_lock(&p->back->think_lock);
		if (p->n_philo > 1)
		{
			if (p->eat_time > p->sleep_time)
				wait_in_ms(p, p->eat_time / 2);
			pthread_mutex_unlock(&p->back->think_lock);
			return ;
		}
		pthread_mutex_unlock(&p->back->think_lock);
	}
}

static void	philo_sleeping(t_philo *p)
{
	print_message(p, "is sleeping");
	wait_in_ms(p, p->sleep_time);
}

void	philo_actions(t_philo *p)
{
	philo_eating(p);
	philo_sleeping(p);
	philo_thinking(p, 1);
}
