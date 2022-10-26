/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:00:29 by chchin            #+#    #+#             */
/*   Updated: 2022/10/25 14:00:31 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_digit(const char *s)
{
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

int	check_args(int argc, char **args)
{
	int	i;
	int	rtn;

	rtn = 1;
	if (argc - 1 < MIN_ARGS)
		rtn = print_error("Too few argument");
	if (argc - 1 > MAX_ARGS)
		rtn = print_error("Too many argument");
	i = 0;
	while (++i < argc)
	{
		if (!ft_digit(args[i]))
			rtn = print_error("Only allow positive integer");
	}
	return (rtn);
}

int	ft_atoi(const char *s)
{
	long	num;

	num = 0;
	while (*s)
	{
		num = num * 10 + (*s - '0');
		s++;
	}
	return (num);
}

int	parse_args(t_info *info, int argc, char **argv)
{
	int	rtn;

	rtn = 1;
	info->num_of_philo = ft_atoi(argv[1]);
	if (info->num_of_philo < 0)
		rtn = print_error("Minimum one philosopher required");
	info->t_to_die = ft_atoi(argv[2]);
	info->t_to_eat = ft_atoi(argv[3]);
	info->t_to_sleep = ft_atoi(argv[4]);
	if (argc - 1 == MAX_ARGS)
	{
		info->num_must_eat = ft_atoi(argv[MAX_ARGS]);
		if (info->num_must_eat < 0)
			rtn = print_error("Minimum one time must eat required");
	}
	return (rtn);
}

t_info	*init_info(int argc, char **argv)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	if (!parse_args(info, argc, argv))
		return (NULL);

}
