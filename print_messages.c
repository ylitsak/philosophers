/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:18:02 by saylital          #+#    #+#             */
/*   Updated: 2024/11/21 11:37:07 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *p, char *msg)
{
	pthread_mutex_lock(&p->back->dead_lock);
	if (p->died[0] == 1)
	{
		pthread_mutex_unlock(&p->back->dead_lock);
		return ;
	}
	pthread_mutex_unlock(&p->back->dead_lock);
	pthread_mutex_lock(&p->back->print_lock);
	printf("%lld %d %s\n",elapsed_time(p), p->p_index, msg);
	pthread_mutex_unlock(&p->back->print_lock);
}
