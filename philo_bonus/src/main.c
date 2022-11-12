/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brook <brook@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:36:42 by brook             #+#    #+#             */
/*   Updated: 2022/11/09 18:38:31 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

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
		pthread_create(&thread, NULL, check_eat, &info);
	pthread_create(&thread, NULL, finish_check, &info);
	join_philo(&info);
	return (0);
}
