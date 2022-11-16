/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brook <brook@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 22:53:32 by brook             #+#    #+#             */
/*   Updated: 2022/11/09 22:53:35 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

int	init_info(t_info *info, int argc, char **argv)
{
	if (check_args(argc, argv) != SUCCESS)
		return (FAILURE);
	if (parse_args(info, argc, argv) != SUCCESS)
		return (FAILURE);
	if (info->num_of_philo == 1)
	{
		printf("0\t1\thas taken a fork\n");
		printf("%d\t1\tis died\n", (int)info->t_to_die);
		return (FAILURE);
	}
	info->philo = malloc(sizeof(t_philo) * (info->num_of_philo + 1));
	if (info->philo == NULL)
		return (FAILURE);
	memset(info->philo, 0, sizeof(t_philo));
	info->m_fork = malloc(sizeof(pthread_mutex_t) * (info->num_of_philo + 1));
	memset(info->philo, 0, sizeof(pthread_mutex_t));
	pthread_mutex_init(&info->m_finish, NULL);
	pthread_mutex_init(&info->m_eat_finish, NULL);
	pthread_mutex_init(&info->m_write, NULL);
	return (SUCCESS);
}

void	init_philo(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		info->philo[i].id = i + 1;
		info->philo[i].info = info;
		pthread_mutex_init(&info->m_fork[i], NULL);
		pthread_mutex_init(&info->philo[i].m_check, NULL);
		if (i == 0)
			info->philo[i].left = &info->m_fork[info->num_of_philo - 1];
		else
			info->philo[i].left = &info->m_fork[i - 1];
		info->philo[i].right = &info->m_fork[i];
		++i;
	}
}
