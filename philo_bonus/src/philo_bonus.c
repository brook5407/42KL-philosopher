/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:56:29 by chchin            #+#    #+#             */
/*   Updated: 2022/11/10 10:39:51 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	*finish_check(void *data)
{
	t_info	*info;
	int		i;

	info = data;
	sem_wait(info->s_finish);
	i = 0;
	while (i < info->num_of_philo)
		kill(info->philo[i++].pid, SIGTERM);
	return (NULL);
}

void	*check_eat(void *data)
{
	t_info	*info;
	int		i;

	info = data;
	i = 0;
	while (i < info->num_of_philo)
		sem_wait(info->s_eat_finish);
	sem_post(info->s_finish);
	return (NULL);
}

void	*check_death(void *data)
{
	t_philo	*philo;
	time_t	t_no_eat;

	philo = data;
	while (1)
	{
		t_no_eat = get_cur_time() - get_last_meal(philo);
		if (t_no_eat >= philo->info->t_to_die)
		{
			print_status(philo, DIED);
			sem_post(philo->info->s_finish);
			return (NULL);
		}
		sem_post(philo->info->s_acting);
	}
	return (NULL);
}

void	fork_philo(t_info *info)
{
	int			i;

	info->t_start = get_cur_time();
	i = 0;
	while (i < info->num_of_philo)
	{
		info->philo[i].last_eat = info->t_start;
		info->philo[i].pid = fork();
		if (info->philo[i].pid == 0)
			return (routine(&info->philo[i]));
		else if (info->philo[i].pid < 0)
		{
			print_error("fork failed");
			exit(1);
		}
		i++;
	}
}

void	join_philo(t_info *info)
{
	int	i;
	int	status;

	i = 0;
	while (i < info->num_of_philo)
		waitpid(info->philo[i++].pid, &status, 0);
}

//void	exit_philo(t_info *info)
//{
//}
