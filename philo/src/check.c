/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:56:29 by chchin            #+#    #+#             */
/*   Updated: 2022/11/12 14:02:57 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*check_eat(void *data)
{
	t_info	*info;

	info = data;
	while (!get_finish(info))
	{
		if (info->num_of_philo == get_eat_finish(info))
			set_finish(info);
	}
	return (NULL);
}

void	*check_death(void *data)
{
	t_philo	*philo;
	time_t	t_no_eat;

	philo = data;
	while (!get_finish(philo->info))
	{
		t_no_eat = get_cur_time() - get_last_meal(philo);
		if (t_no_eat >= philo->info->t_to_die && !get_finish(philo->info))
		{
			print_status(philo, DIED);
			set_finish(philo->info);
		}
	}
	return (NULL);
}
