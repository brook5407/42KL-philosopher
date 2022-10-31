/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:56:17 by chchin            #+#    #+#             */
/*   Updated: 2022/10/26 11:56:18 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *msg)
{
	printf("%sERROR: %s.%s\n", RED, msg, NC);
	return (FAILURE);
}

void	print_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->info->m_write);
	printf("%d\t%d\t%s\n", (int)get_current_ms(), philo->id + 1, msg);
	pthread_mutex_unlock(&philo->info->m_write);
}