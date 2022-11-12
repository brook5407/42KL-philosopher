/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:39:37 by chchin            #+#    #+#             */
/*   Updated: 2022/11/12 13:55:13 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

void	print_status(t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->info->m_write);
	if (!philo->info->finish)
	{
		time = (int)get_timestamp(philo->info);
		if (philo->state == TAKING)
			printf("%d\t%d\t%s\n", time, philo->id, "has taken a fork");
		else if (philo->state == EATING)
			printf("%d\t%d\t%s\n", time, philo->id, "is eating");
		else if (philo->state == SLEEPING)
			printf("%d\t%d\t%s\n", time, philo->id, "is sleeping");
		else if (philo->state == THINKING)
			printf("%d\t%d\t%s\n", time, philo->id, "is thinking");
		else if (philo->state == DIED)
		{
			printf("%d\t%d\t%s\n", time, philo->id, "is die");
			philo->info->finish += 1;
		}
	}
	pthread_mutex_unlock(&philo->info->m_write);
}
