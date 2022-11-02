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

#include "philo.h"

void	routine_take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->left);
	print_status(philo, "has taken a fork");
}

void	routine_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_check);
	philo->last_eat = get_cur_time();
	pthread_mutex_lock(&philo->info->m_finish);
	if (!philo->info->finish)
		print_status(philo, "is eating");
	philo->count_eat += 1;
	if (philo->count_eat == philo->info->num_must_eat)
		philo->info->num_eat_finish += 1;
	pthread_mutex_unlock(&philo->info->m_finish);
	usleep(philo->info->t_to_eat * 1000);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(&philo->m_check);
}

void	routine_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_check);
	print_status(philo, "is sleeping");
	pthread_mutex_unlock(&philo->m_check);
	usleep(philo->info->t_to_sleep * 1000);
}

void	routine_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_check);
	print_status(philo, "is thinking");
	pthread_mutex_unlock(&philo->m_check);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = data;
	if (philo->id % 2 == 0)
		usleep(philo->info->t_to_eat * 1000);
	while (!philo->info->finish)
	{
		routine_take_fork(philo);
		routine_eat(philo);
		routine_sleeping(philo);
		routine_thinking(philo);
	}
	return (NULL);
}