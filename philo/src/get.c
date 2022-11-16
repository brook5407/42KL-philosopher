/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:16:14 by chchin            #+#    #+#             */
/*   Updated: 2022/11/12 13:48:17 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

time_t	get_cur_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

time_t	get_timestamp(t_info *info)
{
	return (get_cur_time() - info->t_start);
}

time_t	get_last_meal(t_philo *philo)
{
	time_t	value;

	pthread_mutex_lock(&philo->m_check);
	value = philo->last_eat;
	pthread_mutex_unlock(&philo->m_check);
	return (value);
}

int	get_finish(t_info *info)
{
	int	value;

	pthread_mutex_lock(&info->m_finish);
	value = info->finish;
	pthread_mutex_unlock(&info->m_finish);
	return (value);
}

int	get_eat_finish(t_info *info)
{
	int	value;

	pthread_mutex_lock(&info->m_eat_finish);
	value = info->num_eat_finish;
	pthread_mutex_unlock(&info->m_eat_finish);
	return (value);
}
