/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:56:29 by chchin            #+#    #+#             */
/*   Updated: 2022/11/10 10:39:51 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	*finish_check(void *arg)
{
	int		i;
	t_table	*table;

	table = arg;
	sem_wait(table->s_finish);
	i = 0;
	while (i < table->num_of_philo)
		kill(table->philos[i++].pid, SIGTERM);
	return (NULL);
}

void	*check_win(void *arg)
{
	t_table	*table;
	int		i;

	table = arg;
	i = 0;
	while (i++ < table->num_of_philo)
		sem_wait(table->s_eat_finish);
	sem_post(table->s_finish);
	return (NULL);
}

void	*check_die(void *arg)
{
	t_philo	*philo;
	time_t	ms;

	philo = arg;
	while (1)
	{
		sem_wait(philo->s_check);
		sem_wait(philo->table->s_write);
		ms = get_cur_time() - philo->last_eat;
		if (ms >= philo->table->t_to_die)
		{
			printf("%d\t%d\t %s\n", (int)get_timestamp(philo->table), \
				philo->id + 1, "died");
			sem_post(philo->table->s_finish);
			return (NULL);
		}
		sem_post(philo->table->s_write);
		sem_post(philo->s_check);
	}
	return (NULL);
}
