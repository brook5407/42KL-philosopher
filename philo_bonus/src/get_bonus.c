/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brook <brook@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:10:33 by brook             #+#    #+#             */
/*   Updated: 2022/11/10 10:39:51 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

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

	sem_wait(philo->s_last_eat);
	value = philo->last_eat;
	sem_post(philo->s_last_eat);
	return (value);
}

void	set_last_eat(t_philo *philo, time_t time_eat)
{
	sem_wait(philo->s_last_eat);
	philo->last_eat = time_eat;
	sem_wait(philo->s_last_eat);
}