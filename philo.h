#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

# define NC		"\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"

# define MIN_ARGS	4
# define MAX_ARGS	5

# define FAILURE	0
# define SUCCESS	1

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
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
	pthread_mutex_t	*m_check;
	pthread_mutex_t	*m_state;
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
	pthread_mutex_t	*m_death;
	t_philo			*philo;
}	t_info;

int		ft_isdigit(const char *s);
int		ft_atoi(const char *s);

time_t	get_cur_time(void);
time_t	get_timestamp(time_t start);
t_state	get_state(t_philo *philo);
time_t	get_last_meal(t_philo *philo);

void	set_death_value(t_info *info);

int		print_error(char *msg);
void	print_status(t_philo *philo, char *msg);

int		init_info(t_info *info, int argc, char **argv);
void	init_philo(t_info *info);
void	create_philo(t_info *info);
void	join_philo(t_info *info);
void	exit_philo(t_info *info);
void	*routine(void *data);

#endif
