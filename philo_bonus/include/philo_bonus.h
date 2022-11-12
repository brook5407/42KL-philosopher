#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
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
	int				count_eat;
	time_t			last_eat;
	pid_t			pid;
	sem_t			*s_last_eat;
	struct s_info	*info;
}	t_philo;

typedef struct s_info
{
	int		num_of_philo;
	time_t	t_start;
	time_t	t_to_die;
	time_t	t_to_eat;
	time_t	t_to_sleep;
	int		num_must_eat;
	sem_t	*s_acting;
	sem_t	*s_eat_finish;
	sem_t	*s_finish;
	sem_t	*s_write;
	sem_t	*s_fork;
	t_philo	*philo;
}	t_info;

int		ft_isdigit(const char *s);
int		ft_atoi(const char *s);

time_t	get_cur_time(void);
time_t	get_timestamp(t_info *info);
time_t	get_last_meal(t_philo *philo)

void	set_last_eat(t_philo *philo, time_t time_eat);

char	*philo_sem_join(char *str, int num);
int		print_error(char *msg);
void	print_status(t_philo *philo, t_state state);

int		init_info(t_info *info, int argc, char **argv);
void	init_philo(t_info *info);
void	*routine(t_philo *philo);
#endif
