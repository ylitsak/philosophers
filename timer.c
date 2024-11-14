/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:14:14 by saylital          #+#    #+#             */
/*   Updated: 2024/11/14 12:13:44 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	elapsed_time(t_philo *p)
{
	struct timeval	end;
	long long		result;

	gettimeofday(&end, NULL);
	result = (end.tv_sec * 1000) + (end.tv_usec / 1000) - p->start_time;
	return (result);
}
long long	start_time(void)
{
	struct timeval	start;
	long long		result;

	gettimeofday(&start, NULL);
	result = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	return (result);
}