/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:16:14 by chchin            #+#    #+#             */
/*   Updated: 2022/10/27 14:16:15 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

time_t	get_cur_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

time_t	get_timestamp(time_t start)
{
	return (get_cur_time() - start);
}

t_state	get_state(t_philo *philo)
{
	t_state	value;

	pthread_mutex_lock(philo->m_state);
	value = philo->state;
	pthread_mutex_unlock(philo->m_state);
	return (value);
}

time_t	get_last_meal(t_philo *philo)
{
	time_t	value;

	pthread_mutex_lock(philo->m_check);
	value = philo->last_eat;
	pthread_mutex_unlock(philo->m_check);
	return (value);
}

//int	get_num_eat(t_philo *philo)
//{
//	int	value;
//
//	pthread_mutex_lock(philo->m_check);
//	value = philo->count_eat;
//	pthread_mutex_unlock(philo->m_check);
//	return (value);
//}