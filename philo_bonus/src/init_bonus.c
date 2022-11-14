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
		if (!ft_isdigit(argv[i]))
			return (print_error("Only allow positive integer"));
	}
	return (SUCCESS);
}

static int	parse_args(t_info *info, int argc, char *argv[])
{
	info->num_of_philo = ft_atoi(argv[1]);
	if (info->num_of_philo <= 0)
		return (print_error("Minimum one philosopher required"));
	info->t_to_die = ft_atoi(argv[2]);
	info->t_to_eat = ft_atoi(argv[3]);
	info->t_to_sleep = ft_atoi(argv[4]);
	if (argc - 1 == MAX_ARGS)
	{
		info->num_must_eat = ft_atoi(argv[MAX_ARGS]);
		if (info->num_must_eat <= 0)
			return (print_error("Minimum one time must eat required"));
	}
	return (SUCCESS);
}

static sem_t	*philo_sem_init(const char *name, unsigned int value)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (sem != SEM_FAILED)
		return (sem);
	sem_unlink(name);
	return (sem);
}

int	init_info(t_info *info, int argc, char **argv)
{
	if (check_args(argc, argv) != SUCCESS)
		return (FAILURE);
	if (parse_args(info, argc, argv) != SUCCESS)
		return (FAILURE);
	info->philo = malloc(sizeof(t_philo) * (info->num_of_philo + 1));
	if (info->philo == NULL)
		return (FAILURE);
	info->s_fork = philo_sem_init("forks", info->num_of_philo + 1);
	info->s_finish = philo_sem_init("finish", 0);
	info->s_eat_finish = philo_sem_init("eat finish", 0);
	info->s_write = philo_sem_init("write", 1);
	return (SUCCESS);
}

void	init_philo(t_info *info)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < info->num_of_philo)
	{
		info->philo[i].id = i + 1;
		info->philo[i].info = info;
		info->philo[i].count_eat = 0;
		info->philo[i].last_eat = 0;
		tmp = philo_sem_join("check", info->philo[i].id);
		info->philo[i].s_check = philo_sem_init(tmp, 1);
		free(tmp);
		++i;
	}
}