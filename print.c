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
	return (0);
}

void	print_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->info->m_write);

}