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

static void	fork_philos(t_table *table)
{
	int	i;
	int	pid;

	i = 0;
	table->t_start = get_cur_time();
	while (i < table->num_of_philo)
	{
		table->philos[i].last_eat = table->t_start;
		pid = fork();
		if (pid == 0)
			routine(&table->philos[i]);
		table->philos[i++].pid = pid;
	}
}

static void	join_philos(void)
{
	while (waitpid(-1, NULL, 0) != -1)
		;
}

static void	exit_philos(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->num_of_philo)
		sem_close(table->philos[i++].s_check);
	free(table->philos);
	sem_close(table->s_finish);
	sem_close(table->s_write);
	sem_close(table->s_forks);
	sem_close(table->s_eat_finish);
}

int	main(int argc, char *argv[])
{
	t_table		table;
	pthread_t	thread;

	memset(&table, 0, sizeof(table));
	if (init(&table, argc, argv))
		return (1);
	fork_philos(&table);
	if (table.num_must_eat != 0)
		pthread_create(&thread, NULL, check_win, &table);
	pthread_create(&thread, NULL, finish_check, &table);
	pthread_detach(thread);
	join_philos();
	exit_philos(&table);
	return (0);
}
