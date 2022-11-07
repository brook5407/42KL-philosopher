/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:29:18 by chchin            #+#    #+#             */
/*   Updated: 2022/10/31 15:29:19 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	routine_take_fork(t_philo *philo)
{
	set_state(philo, TAKING);
	pthread_mutex_lock(philo->left);
	print_status(philo, "has taken a fork", PURPLE);
	pthread_mutex_lock(philo->right);
	print_status(philo, "has taken a fork", PURPLE);
	set_state(philo, INITIAL);
}

void	routine_eat(t_philo *philo)
{
	set_last_eat(philo, get_cur_time());
	print_status(philo, "is eating", GREEN);
	set_state(philo, EATING);
	philo->count_eat += 1;
	if (philo->count_eat == philo->info->num_must_eat)
		philo->info->num_eat_finish += 1;
	usleep(philo->info->t_to_eat * 1000);
	set_state(philo, INITIAL);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
}

void	routine_sleeping(t_philo *philo)
{
	set_state(philo, SLEEPING);
	print_status(philo, "is sleeping", CYAN);
	usleep(philo->info->t_to_sleep * 1000);
	set_state(philo, INITIAL);
}

void	routine_thinking(t_philo *philo)
{
	set_state(philo, THINKING);
	print_status(philo, "is thinking", YELLOW);
	set_state(philo, INITIAL);
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
	while (!philo->info->finish)
	{
		routine_take_fork(philo);
		routine_eat(philo);
		routine_sleeping(philo);
		routine_thinking(philo);
	}
	return (NULL);
}
