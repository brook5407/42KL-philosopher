/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:56:29 by chchin            #+#    #+#             */
/*   Updated: 2022/11/12 14:02:57 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*monitoring_check_eat(void *data)
{
	t_info	*info;

	info = data;
	while (!info->finish)
	{
		pthread_mutex_lock(&info->m_finish);
		if (info->num_eat_finish == info->num_of_philo)
			info->finish = 1;
		pthread_mutex_unlock(&info->m_finish);
	}
	return (NULL);
}

void	*monitoring_check_death(void *data)
{
	t_philo	*philo;
	time_t	t_no_eat;

	philo = data;
	while (!philo->info->finish)
	{
		pthread_mutex_lock(&philo->info->m_finish);
		t_no_eat = get_cur_time() - get_last_meal(philo);
		if (t_no_eat >= philo->info->t_to_die && !philo->info->finish)
		{
			set_state(philo, DIED);
			print_status(philo);
		}
		pthread_mutex_unlock(&philo->info->m_finish);
	}
	return (NULL);
}
