/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brook <brook@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:39:03 by brook             #+#    #+#             */
/*   Updated: 2022/11/09 20:08:13 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static sem_t	*philo_sem_init(const char *name, unsigned int value)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	sem_unlink(name);
	return (sem);
}

static int	check_args(int argc, char **argv)
{
	int	i;

	if (argc - 1 < MIN_ARGS)
		return (print_error("Too few argument"));
	if (argc - 1 > MAX_ARGS)
		return (print_error("Too many argument"));
	i = 0;
	while (++i < argc)
	{
		if (ft_isdigit(argv[i]))
			return (print_error("Only allow positive integer"));
	}
	return (SUCCESS);
}

static int	parsing_args(t_table *table, int argc, char *argv[])
{
	table->num_of_philo = ft_atoi(argv[1]);
	if (table->num_of_philo <= 0)
		return (print_error("Minimum one philosopher required"));
	table->t_to_die = ft_atoi(argv[2]);
	table->t_to_eat = ft_atoi(argv[3]);
	table->t_to_sleep = ft_atoi(argv[4]);
	if (argc - 1 == MAX_ARGS)
	{
		table->num_must_eat = ft_atoi(argv[MAX_ARGS]);
		if (table->num_must_eat <= 0)
			return (print_error("Minimum one time must eat required"));
	}
	return (SUCCESS);
}

static void	init_philos(t_table *table)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < table->num_of_philo)
	{
		tmp = philo_sem_join("philo", i);
		table->philos[i].s_check = philo_sem_init(tmp, 1);
		free(tmp);
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].count_eat = 0;
		table->philos[i].last_eat = 0;
		++i;
	}
}

int	init(t_table *table, int argc, char **argv)
{
	if (check_args(argc, argv) != SUCCESS)
		return (FAILURE);
	if (parsing_args(table, argc, argv) != SUCCESS)
		return (FAILURE);
	table->philos = malloc(sizeof(t_philo) * (table->num_of_philo + 1));
	if (table->philos == NULL)
		return (FAILURE);
	init_philos(table);
	table->s_forks = philo_sem_init("forks", table->num_of_philo + 1);
	table->s_finish = philo_sem_init("finish", 0);
	table->s_eat_finish = philo_sem_init("eat finish", 0);
	table->s_write = philo_sem_init("write", 1);
	return (SUCCESS);
}
