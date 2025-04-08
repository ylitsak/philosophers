/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:12:06 by saylital          #+#    #+#             */
/*   Updated: 2025/04/08 19:13:32 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *p, char *msg)
{
	pthread_mutex_lock(&p->back->print_lock);
	pthread_mutex_lock(&p->back->dead_lock);
	if (p->died[0] == 1 || p->eaten == 0)
	{
		pthread_mutex_unlock(&p->back->dead_lock);
		pthread_mutex_unlock(&p->back->print_lock);
		return ;
	}
	pthread_mutex_unlock(&p->back->dead_lock);
	printf("%lld %d %s\n", elapsed_time(p), p->p_index, msg);
	pthread_mutex_unlock(&p->back->print_lock);
}

void	print_error(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	write(fd, s, i);
	write(fd, "\n", 2);
}
