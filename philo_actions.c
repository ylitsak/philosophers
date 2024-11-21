/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:03:56 by saylital          #+#    #+#             */
/*   Updated: 2024/11/21 15:14:26 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eating(t_philo *p)
{
	// if (p->p_index % 2 == 1)
	// {
	// 	pthread_mutex_lock(p->left_fork);
	// 	print_message(p, "has taken a fork");
	// 	pthread_mutex_lock(p->right_fork);

	// }
	// else
	// {
	// 	pthread_mutex_lock(p->right_fork);
	// 	print_message(p, "has taken a fork");
	// 	pthread_mutex_lock(p->left_fork);	
	// }
	pthread_mutex_lock(p->right_fork);
	print_message(p, "has taken a fork");
	pthread_mutex_lock(p->left_fork);
	print_message(p, "has taken a fork");
	print_message(p, "is eating");
	if (p->eaten > 0)
		p->eaten--;
	p->last_meal = start_time();
	ft_usleep(p, p->eat_time);
	pthread_mutex_unlock(p->right_fork);
	pthread_mutex_unlock(p->left_fork);
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
