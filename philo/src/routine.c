/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:29:18 by chchin            #+#    #+#             */
/*   Updated: 2022/11/12 13:46:13 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	routine_take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	print_status(philo, TAKING);
	pthread_mutex_lock(philo->right);
	print_status(philo, TAKING);
}

void	routine_eat(t_philo *philo)
{
	print_status(philo, EATING);
	set_last_eat(philo, get_cur_time());
	philo->count_eat += 1;
	if (philo->count_eat == philo->info->num_must_eat)
		set_eat_finish(philo->info);
	usleep(philo->info->t_to_eat * 1000);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
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

void	*routine(void *data)
{
	t_philo	*philo;

	philo = data;
	if (philo->id % 2 == 0)
	{
		if (philo->info->t_to_eat == 0)
			usleep(1000);
		else
			usleep(philo->info->t_to_eat * 1000);
	}
	while (!get_finish(philo->info))
	{
		routine_take_fork(philo);
		routine_eat(philo);
		routine_sleeping(philo);
		routine_thinking(philo);
	}
	return (NULL);
}
