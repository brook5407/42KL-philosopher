/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:07:13 by chchin            #+#    #+#             */
/*   Updated: 2022/11/15 12:07:15 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_finish(t_info *info)
{
	pthread_mutex_lock(&info->m_finish);
	info->finish = 1;
	pthread_mutex_unlock(&info->m_finish);
}

void	set_eat_finish(t_info *info)
{
	pthread_mutex_lock(&info->m_eat_finish);
	info->num_eat_finish += 1;
	pthread_mutex_unlock(&info->m_eat_finish);
}

void	set_last_eat(t_philo *philo, time_t time_eat)
{
	pthread_mutex_lock(&philo->m_check);
	philo->last_eat = time_eat;
	pthread_mutex_unlock(&philo->m_check);
}
