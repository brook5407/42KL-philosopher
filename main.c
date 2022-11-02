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

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info	info;

	memset(&info, 0, sizeof(info));
	if (init_info(&info, argc, argv) != SUCCESS)
		return (0);
	init_philo(&info);
	create_philo(&info);
	join_philo(&info);
	exit_philo(&info);
	return (0);
}
