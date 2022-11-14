/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:33:11 by chchin            #+#    #+#             */
/*   Updated: 2022/11/09 22:16:34 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	create_philo(t_info *info)
{
	int			i;
	pthread_t	thread;

	info->t_start = get_cur_time();
	i = 0;
	while (i < info->num_of_philo)
	{
		info->philo[i].last_eat = info->t_start;
		pthread_create(&info->philo[i].thread, NULL, routine, &info->philo[i]);
		pthread_create(&thread, NULL, monitoring_check_death, &info->philo[i]);
		pthread_detach(thread);
		i++;
	}
	if (info->num_must_eat != 0)
	{
		pthread_create(&thread, NULL, monitoring_check_eat, info);
		pthread_detach(thread);
	}
}

static void	join_philo(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
		pthread_join(info->philo[i++].thread, NULL);
}

static void	exit_philo(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_mutex_destroy(&info->m_fork[i]);
		pthread_mutex_destroy(&info->philo[i].m_check);
		pthread_mutex_destroy(&info->philo[i].m_state);
		i++;
	}
	pthread_mutex_destroy(&info->m_finish);
	pthread_mutex_destroy(&info->m_write);
	free(info->m_fork);
	free(info->philo);
}

int	main(int argc, char **argv)
{
	t_info	info;

	memset(&info, 0, sizeof(info));
	if (init_info(&info, argc, argv) != SUCCESS)
		return (0);
	init_philo(&info);
	create_philo(&info);
	join_philo(&info);
	exit_philo(&info);
	return (0);
}
