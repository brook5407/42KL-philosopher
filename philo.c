/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:56:29 by chchin            #+#    #+#             */
/*   Updated: 2022/10/26 11:56:30 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring_must_eat(void *data)
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

void	*monitoring_thread(void *data)
{
	t_philo		*philo;
	time_t		t_no_eat;

	philo = data;
	while (!philo->info->finish)
	{
		pthread_mutex_lock(&philo->m_check);
		pthread_mutex_lock(&philo->info->m_finish);
		t_no_eat = get_current_ms() - philo->last_eat;
		if (t_no_eat >= philo->info->t_to_die && !philo->info->finish)
		{
			print_status(philo, "died");
			philo->info->finish = 1;
		}
		pthread_mutex_unlock(&philo->info->m_finish);
		pthread_mutex_unlock(&philo->m_check);
	}
	return (NULL);
}

void	create_philo(t_info *info)
{
	int			i;
	pthread_t	thread;

	info->t_start = get_current_ms();
	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_create(&info->philo[i].thread, NULL, philo, &info->philo[i]);
		info->philo[i].last_eat = info->t_start;
		pthread_create(&thread, NULL, monitoring_thread, &info->philo[i]);
		pthread_detach(thread);
		i++;
	}
	if (info->num_must_eat != 0)
	{
		pthread_create(&thread, NULL, monitoring_must_eat, &info);
		pthread_detach(thread);
	}
}
