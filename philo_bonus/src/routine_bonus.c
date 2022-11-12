/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:29:18 by chchin            #+#    #+#             */
/*   Updated: 2022/11/09 23:34:12 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	routine_take_fork(t_philo *philo)
{
	sem_wait(philo->info->s_fork);
	print_status(philo, TAKING);
	sem_wait(philo->info->s_fork);
	print_status(philo);
}

void	routine_eat(t_philo *philo)
{
	print_status(philo, EATING);
	set_last_eat(philo, get_cur_time());
	philo->count_eat += 1;
	if (philo->count_eat == philo->info->num_must_eat)
		sem_post(philo->info->s_eat_finish);
	usleep(philo->info->t_to_eat * 1000);
	sem_wait(philo->info->s_fork);
	sem_wait(philo->info->s_fork);
}

void	routine_sleeping(t_philo *philo)
{
	print_status(philo, SLEEPING);
	usleep(philo->info->t_to_sleep * 1000);
}

void	routine_thinking(t_philo *philo)
{
	print_status(philo, THINKING);
}

void	*routine(t_philo *philo)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, monitor, philo);
	if (philo->id % 2 == 0)
	{
		if (philo->info->t_to_eat == 0)
			usleep(500);
		else
			usleep(philo->info->t_to_eat * 1000);
	}
	while (1)
	{
		routine_take_fork(philo);
		routine_eat(philo);
		routine_sleeping(philo);
		routine_thinking(philo);
	}
	exit(0);
}
