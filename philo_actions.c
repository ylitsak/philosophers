/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:03:56 by saylital          #+#    #+#             */
/*   Updated: 2025/03/23 22:03:11 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eat(t_philo *p)
{
	print_message(p, "is eating");
	if (p->eaten > 0)
		p->eaten--;
	p->last_meal = start_time();
	ft_usleep(p, p->eat_time);
}

void	philo_eating(t_philo *p)
{
	if (p->p_index % 2 != 0)
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
	if (p->p_index % 2 == 0)
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

void	philo_thinking(t_philo *p)
{
	print_message(p, "is thinking");
}

void	philo_sleeping(t_philo *p)
{
	print_message(p, "is sleeping");
	ft_usleep(p, p->sleep_time);
}
