/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:39:37 by chchin            #+#    #+#             */
/*   Updated: 2022/10/27 11:39:38 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(const char *s)
{
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (FAILURE);
		s++;
	}
	return (SUCCESS);
}

int	ft_atoi(const char *s)
{
	int	num;

	num = 0;
	while (*s)
		num = num * 10 + (*s++ - '0');
	return (num);
}

int	print_error(char *msg)
{
	printf("%sERROR: %s.%s\n", RED, msg, NC);
	return (FAILURE);
}

void	print_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->info->m_write);
	printf("%d\t%d\t%s\n", (int)get_timestamp(philo->info->t_start), \
	philo->id, msg);
	pthread_mutex_unlock(&philo->info->m_write);
}
