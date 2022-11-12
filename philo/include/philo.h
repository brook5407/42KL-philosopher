#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

/* ************************* DEFINES ************************** */

# define NC		"\e[0m"
# define RED	"\e[31m"

# define MIN_ARGS	4
# define MAX_ARGS	5

# define FAILURE	0
# define SUCCESS	1

/* ************************* STRUCT ************************** */

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	TAKING,
	INITIAL,
}	t_state;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				count_eat;
	time_t			last_eat;
	struct s_info	*info;
	t_state			state;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	m_check;
	pthread_mutex_t	m_state;
}	t_philo;

typedef struct s_info
{
	int				num_of_philo;
	time_t			t_start;
	time_t			t_to_die;
	time_t			t_to_eat;
	time_t			t_to_sleep;
	int				num_must_eat;
	int				num_eat_finish;
	int				finish;
	pthread_mutex_t	m_finish;
	pthread_mutex_t	m_write;
	pthread_mutex_t	*m_fork;
	t_philo			*philo;
}	t_info;

int		ft_isdigit(const char *s);
int		ft_atoi(const char *s);

time_t	get_cur_time(void);
time_t	get_timestamp(t_info *info);
t_state	get_state(t_philo *philo);
time_t	get_last_meal(t_philo *philo);

void	set_state(t_philo *philo, t_state state);
void	set_last_eat(t_philo *philo, time_t time_eat);

int		print_error(char *msg);
void	print_status(t_philo *philo);

int		init_info(t_info *info, int argc, char **argv);
void	init_philo(t_info *info);
void	create_philo(t_info *info);
void	join_philo(t_info *info);
void	exit_philo(t_info *info);
void	*routine(void *data);

#endif
