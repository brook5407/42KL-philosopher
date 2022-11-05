/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:19:11 by chchin            #+#    #+#             */
/*   Updated: 2022/11/05 14:19:12 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	threads_run(t_info *info)
{
	int	i;

	pthread_mutex_init(&info->m_finish, NULL);
	pthread_mutex_init(&info->m_write, NULL);
	pthread_mutex_init(info->m_death, NULL);
	init_philo(info);
	create_philo(info);
}
