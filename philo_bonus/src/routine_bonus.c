/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:29:18 by chchin            #+#    #+#             */
/*   Updated: 2022/11/09 23:34:12 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	routine_take_fork(t_philo *philo)
{
	sem_wait(philo->table->s_forks);
	print_status(philo, TAKING);
	sem_wait(philo->table->s_forks);
	print_status(philo, TAKING);
}

static void	routine_eat(t_philo *philo)
{
	sem_wait(philo->s_check);
	philo->last_eat = get_cur_time();
	print_status(philo, EATING);
	philo->count_eat += 1;
	if (philo->count_eat == philo->table->num_must_eat)
		sem_post(philo->table->s_eat_finish);
	usleep(philo->table->t_to_eat * 1000);
	sem_post(philo->table->s_forks);
	sem_post(philo->table->s_forks);
	sem_post(philo->s_check);
}

static void	routine_sleeping(t_philo *philo)
{
	print_status(philo, SLEEPING);
	usleep(philo->table->t_to_sleep * 1000);
}

static void	routine_thinking(t_philo *philo)
{
	print_status(philo, THINKING);
}

void	routine(t_philo *philo)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, check_die, philo);
	if (philo->id % 2 == 0)
		usleep(philo->table->t_to_eat * 1000);
	while (1)
	{
		routine_take_fork(philo);
		routine_eat(philo);
		routine_sleeping(philo);
		routine_thinking(philo);
	}
	exit(0);
}
