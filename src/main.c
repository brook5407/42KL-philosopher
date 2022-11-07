/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:33:11 by chchin            #+#    #+#             */
/*   Updated: 2022/10/26 13:33:13 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	threads_run(t_info *info)
{
	int	i;

	pthread_mutex_init(&info->m_finish, NULL);
	pthread_mutex_init(&info->m_write, NULL);
	pthread_mutex_init(info->m_death, NULL);
	init_philo(info);
	create_philo(info);
//	monitoring_death(info);
	join_philo(info);
}

int	main(int argc, char **argv)
{
	t_info	info;

	memset(&info, 0, sizeof(info));
	if (init_info(&info, argc, argv) != SUCCESS)
		return (0);
	threads_run(&info);
	exit_philo(&info);
	return (0);
}
