/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:13:06 by chchin            #+#    #+#             */
/*   Updated: 2022/11/05 15:13:07 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_death_value(t_info *info)
{
	pthread_mutex_lock(info->m_death, NULL);
	info->finish = 1;
	pthread_mutex_unlock(info->m_death, NULL);
}