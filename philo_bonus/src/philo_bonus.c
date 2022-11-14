/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brook <brook@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:36:42 by brook             #+#    #+#             */
/*   Updated: 2022/11/09 18:38:31 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	fork_philo(t_info *info)
{
	int	i;
	int	pid;

	info->t_start = get_cur_time();
	i = 0;
	while (i < info->num_of_philo)
	{
		info->philo[i].last_eat = info->t_start;
		pid = fork();
		if (pid == 0)
		{
			routine(&info->philo[i]);
			exit_philo(info);
		}
		info->philo[i++].pid = pid;
	}
}

void	join_philo(void)
{
	while (waitpid(-1, NULL, 0) != -1)
		;
}

void	exit_philo(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
		sem_close(info->philo[i++].s_check);
	free(info->philo);
	sem_close(info->s_finish);
	sem_close(info->s_fork);
	sem_close(info->s_write);
	sem_close(info->s_eat_finish);
}

int	main(int argc, char **argv)
{
	t_info		info;
	pthread_t	thread;

	memset(&info, 0, sizeof(info));
	if (init_info(&info, argc, argv) != SUCCESS)
		return (0);
	init_philo(&info);
	fork_philo(&info);
	if (info.num_must_eat)
	{
		pthread_create(&thread, NULL, check_eat, &info);
		pthread_detach(thread);
	}
	pthread_create(&thread, NULL, finish_check, &info);
	pthread_detach(thread);
	join_philo();
	exit_philo(&info);
	return (0);
}
