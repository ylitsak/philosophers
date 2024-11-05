/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:50:17 by saylital          #+#    #+#             */
/*   Updated: 2024/11/05 12:43:09 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h> //printf
# include <string.h> //memset
# include <unistd.h> // usleep
# include <stdlib.h> // malloc free
# include <sys/time.h> //gettimeofday
# include <pthread.h> //pthreads and mutex

typedef struct s_philo
{
	int				n_philo;
	int				n_eaten;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*righ_fork;

}	t_philo;

// utils.c
long	ft_atoi_long(char *str);
int		check_input(char *argv[]);

#endif