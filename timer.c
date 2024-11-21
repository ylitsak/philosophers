/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:14:14 by saylital          #+#    #+#             */
/*   Updated: 2024/11/21 11:22:29 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


long long	elapsed_time(t_philo *p)
{
	long long		result;

	result = start_time() - p->start_time;
	return (result);
}
long long	start_time(void)
{
	struct timeval	start;
	long long		result;

	gettimeofday(&start, NULL);
	result = (start.tv_sec * 1000LL) + (start.tv_usec / 1000);
	return (result);
}
void	ft_usleep(t_philo *p, long long time)
{
	long long	start;
	long long	new;

	start = start_time();
	new = start_time();
	while ((start + time) > new)
	{
		usleep(1000);
		if (p->died[0] == 1)
			return ;
		new = start_time();
	}
}