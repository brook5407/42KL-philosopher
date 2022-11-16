/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:13:21 by chchin            #+#    #+#             */
/*   Updated: 2022/11/15 12:13:22 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	m_check;
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
	pthread_mutex_t	m_eat_finish;
	pthread_mutex_t	m_write;
	pthread_mutex_t	*m_fork;
	t_philo			*philo;
}	t_info;

/* ************************ FUNCTION **************************/

int		ft_isdigit(const char *s);
int		ft_atoi(const char *s);

time_t	get_cur_time(void);
time_t	get_timestamp(t_info *info);
time_t	get_last_meal(t_philo *philo);
int		get_finish(t_info *info);
int		get_eat_finish(t_info *info);

void	set_finish(t_info *info);
void	set_last_eat(t_philo *philo, time_t time_eat);
void	set_eat_finish(t_info *info);

int		print_error(char *msg);
void	print_status(t_philo *philo, t_state state);

int		init_info(t_info *info, int argc, char **argv);
void	init_philo(t_info *info);

void	*check_eat(void *data);
void	*check_death(void *data);

void	*routine(void *data);

#endif
