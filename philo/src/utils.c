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

void	print_status(t_philo *philo, t_state state)
{
	int	time;

	pthread_mutex_lock(&philo->info->m_write);
	if (!get_finish(philo->info))
	{
		time = (int)get_timestamp(philo->info);
		if (state == TAKING)
			printf("%d\t%d\t%s\n", time, philo->id, "has taken a fork");
		else if (state == EATING)
			printf("%d\t%d\t%s\n", time, philo->id, "is eating");
		else if (state == SLEEPING)
			printf("%d\t%d\t%s\n", time, philo->id, "is sleeping");
		else if (state == THINKING)
			printf("%d\t%d\t%s\n", time, philo->id, "is thinking");
		else if (state == DIED)
			printf("%d\t%d\t%s\n", time, philo->id, "is die");
	}
	pthread_mutex_unlock(&philo->info->m_write);
}
