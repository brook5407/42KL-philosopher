/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:13:06 by chchin            #+#    #+#             */
/*   Updated: 2022/11/05 15:13:07 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_state(t_philo *philo, t_state state)
{
	pthread_mutex_lock(&philo->m_state);
	philo->state = state;
	pthread_mutex_unlock(&philo->m_state);
}

void	set_last_eat(t_philo *philo, time_t time_eat)
{
	pthread_mutex_lock(&philo->m_check);
	philo->last_eat = time_eat;
	pthread_mutex_unlock(&philo->m_check);
}
