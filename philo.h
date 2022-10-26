#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

# define NC		"\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"

# define MIN_ARGS			4
# define MAX_ARGS			5

typedef enum e_state
{
	EATING = 0,
	SLEEPING = 1,
	THINKING = 2,
	DEAD = 3,
	TAKE_1 = 4,
	TAKE_2 = 5,
}	t_state;

typedef struct s_info
{
	int				num_of_philo;
	time_t			t_start;
	time_t			t_to_die;
	time_t			t_to_eat;
	time_t			t_to_sleep;
	int				num_must_eat;
	time_t			t_end;
	pthread_mutex_t	m_finish;
	pthread_mutex_t	m_write;
	pthread_mutex_t	*m_fork;
	t_philo			*philos;
}	t_info;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	t_info			*info;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	m_check;
	int				count_eat;
	time_t			last_eat;
}	t_philo;

int	print_error(char *msg);

#endif
