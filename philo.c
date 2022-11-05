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

void	*monitoring_eat(t_info *info)
{
	int	i;

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

void	*monitoring_death(t_info *info)
{
	int		i;
	time_t	t_no_eat;

	i = 0;
	while (i < info->num_of_philo)
	{
		if (get_state(info->philo[i]) == EATING)
			continue ;
		pthread_mutex_lock(&info->m_finish);
		t_no_eat = get_cur_time() - get_last_meal(info->philo[i]);
		if (t_no_eat >= philo->info->t_to_die)
		{
			print_status(philo, "died");
			set_death_value(info);
			return ;
		}
		pthread_mutex_unlock(&info->m_finish);
		++i;
	}
}
//	t_philo		*philo;
//	time_t		t_no_eat;
//
//	philo = data;
//	while (!philo->info->finish)
//	{
//		pthread_mutex_lock(&philo->m_check);
//		pthread_mutex_lock(&philo->info->m_finish);
//		t_no_eat = get_cur_time() - philo->last_eat;
//		if (t_no_eat >= philo->info->t_to_die && !philo->info->finish)
//		{
//			print_status(philo, "died");
//			philo->info->finish = 1;
//		}
//		pthread_mutex_unlock(&philo->info->m_finish);
//		pthread_mutex_unlock(&philo->m_check);
//	}
//	return (NULL);
}

void	create_philo(t_info *info)
{
	int			i;

	info->t_start = get_cur_time();
	i = 0;
	while (i < info->num_of_philo)
	{
		info->philo[i].last_eat = info->t_start;
		pthread_create(&info->philo[i].thread, NULL, routine, &info->philo[i]);
		i++;
	}
}

void	join_philo(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
		pthread_join(info->philo[i].thread, NULL);
}

void	exit_philo(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_mutex_destroy(&info->m_fork[i]);
		pthread_mutex_destroy(&info->philo[i].m_check);
		i++;
	}
	pthread_mutex_destroy(&info->m_finish);
	pthread_mutex_destroy(&info->m_write);
	free(info->m_fork);
	free(info->philo);
}
