/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:03:56 by saylital          #+#    #+#             */
/*   Updated: 2024/11/13 15:21:01 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eating(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	pthread_mutex_lock(p->right_fork);
	printf("%d is eating\n", p->p_index);
	usleep(p->eat_time * 1000);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

void	philo_thinking(t_philo *p)
{
	printf("%d is thinking\n", p->p_index);
}

void	philo_sleeping(t_philo *p)
{
	printf("%d is sleeping\n", p->p_index);
	usleep(p->sleep_time * 1000);
}
