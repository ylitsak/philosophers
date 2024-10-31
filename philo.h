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
	int		n_philo;
	int		n_eaten;
	size_t	time_die;
	size_t	time_eat;
	size_t	time_sleep;

}	t_philo;

#endif