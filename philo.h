/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:50:17 by saylital          #+#    #+#             */
/*   Updated: 2024/11/13 15:21:25 by saylital         ###   ########.fr       */
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
	int				p_index;
	int				eaten;
	size_t			die_time;
	size_t			eat_time;
	size_t			sleep_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

}	t_philo;

typedef struct s_lock_struct
{
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_lock_struct;

// utils.c
long	ft_atoi_long(char *str);
int		check_input(char *argv[]);
//init_locks.c
int	init_mutex(t_lock_struct *l, int amount);
//philo_actions
void	philo_eating(t_philo *p);
void	philo_thinking(t_philo *p);
void	philo_sleeping(t_philo *p);

#endif