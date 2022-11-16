/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:35:48 by chchin            #+#    #+#             */
/*   Updated: 2022/11/16 10:35:50 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <signal.h>
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

# define FAILURE	1
# define SUCCESS	0

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
	sem_t			*s_check;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int		num_of_philo;
	time_t	t_start;
	time_t	t_to_die;
	time_t	t_to_eat;
	time_t	t_to_sleep;
	int		num_must_eat;
	sem_t	*s_eat_finish;
	sem_t	*s_finish;
	sem_t	*s_write;
	sem_t	*s_forks;
	t_philo	*philos;
}	t_table;

/* ************************ FUNCTION **************************/

int			ft_atoi(const char *s);
int			ft_isdigit(const char *s);
int			print_error(char *msg);
void		print_status(t_philo *philo, t_state state);
char		*philo_sem_join(char *str, int num);

time_t		get_cur_time(void);
time_t		get_timestamp(t_table *table);

int			init(t_table *table, int argc, char *argv[]);

void		routine(t_philo *philo);

void		*finish_check(void *arg);
void		*check_win(void *argv);
void		*check_die(void *argv);

#endif
