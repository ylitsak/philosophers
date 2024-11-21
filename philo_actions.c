/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:03:56 by saylital          #+#    #+#             */
/*   Updated: 2024/11/21 11:37:18 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eating(t_philo *p)
{

	// if (p->died[0] == 1)
	// 	return ;
	if (p->p_index % 2 == 0)
	{
		pthread_mutex_lock(p->left_fork);
		print_message(p, "has taken a fork");
		pthread_mutex_lock(p->right_fork);

	}
	else
	{
		pthread_mutex_lock(p->right_fork);
		print_message(p, "has taken a fork");
		pthread_mutex_lock(p->left_fork);	
	}
	print_message(p, "has taken a fork");
	print_message(p, "is eating");
	p->last_meal = start_time();
	ft_usleep(p, p->eat_time);
	pthread_mutex_unlock(p->right_fork);
	pthread_mutex_unlock(p->left_fork);
}

void	philo_thinking(t_philo *p)
{
	pthread_mutex_lock(&p->back->dead_lock);
	if (p->died[0] == 1)
	{
		pthread_mutex_unlock(&p->back->dead_lock);
		return ;
	}
	pthread_mutex_unlock(&p->back->dead_lock);
	pthread_mutex_lock(&p->back->print_lock);
	printf("%lld %d is thinking\n",elapsed_time(p), p->p_index);
	pthread_mutex_unlock(&p->back->print_lock);
}

void	philo_sleeping(t_philo *p)
{
	pthread_mutex_lock(&p->back->dead_lock);
	if (p->died[0] == 1)
	{
		pthread_mutex_unlock(&p->back->dead_lock);
		return ;
	}
	pthread_mutex_unlock(&p->back->dead_lock);
	pthread_mutex_lock(&p->back->print_lock);
	printf("%lld %d is sleeping\n",elapsed_time(p), p->p_index);
	pthread_mutex_unlock(&p->back->print_lock);
	ft_usleep(p, p->sleep_time);
}
