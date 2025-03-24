/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:50:17 by saylital          #+#    #+#             */
/*   Updated: 2025/03/24 18:31:54 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h> //printf
# include <unistd.h> // usleep
# include <stdlib.h> // malloc free
# include <sys/time.h> //gettimeofday
# include <pthread.h> //pthreads and mutex

typedef struct s_philo
{
	int						n_philo;
	int						p_index;
	int						eaten;
	int						*died;
	long long				die_time;
	long long				eat_time;
	long long				sleep_time;
	pthread_t				thread;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	struct s_main_struct	*back;
	long long				start_time;
	long long				last_meal;
}	t_philo;

typedef struct s_main_struct
{
	int				is_dead;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	value_lock;
	t_philo			*philos;
}	t_main_struct;

// utils.c
long		ft_atoi_long(char *str);
int			check_input(int argc, char *argv[]);
void		free_and_destroy(int amount, t_main_struct *monitor);
void		print_error(char *s, int fd);
void		print_message(t_philo *p, char *msg);
//init_locks.c
int			init_mutex(t_main_struct *l, int amount);
//philo_actions
void		philo_eating(t_philo *p);
void		philo_thinking(t_philo *p);
void		philo_sleeping(t_philo *p);
//timer.c
long long	start_time(void);
long long	elapsed_time(t_philo *p);
void		wait_in_ms(t_philo *p, long long time);
//print_messages.c
void		print_message(t_philo *p, char *msg);
//create_threads.c
int			create_threads(t_main_struct *monitor, int amount);
//monitoring_threads.c
void		*monitor_thread(void *arg);
void		*routine(void *arg);

#endif