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

void	*monitoring_thread(void *data)
{
	t_philo		*philo;

	philo = data;
	while (!philo->info->death)
	{
		pthread_mutex_lock(&philo->m_check);
		pthread_mutex_lock(&philo->info->m_finish);
		if (get_current_ms() >= philo->info->t_to_die && !philo->info->death)
		{
			print_status(philo, get_current_ms(), "died");
			philo->info->death = 1;
		}
	}
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
		pthread_create(&thread, NULL, monitoring_thread, &info->philo[i])
		pthread_detach(thread);
	}
}
