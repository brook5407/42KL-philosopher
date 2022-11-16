/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brook <brook@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:40:37 by brook             #+#    #+#             */
/*   Updated: 2022/11/09 23:23:10 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	print_status(t_philo *philo, t_state state)
{
	time_t	ms;

	sem_wait(philo->table->s_write);
	ms = get_timestamp(philo->table);
	if (state == TAKING)
		printf("%ld\t%d\t%s\n", ms, philo->id, "has taken a fork");
	else if (state == EATING)
		printf("%ld\t%d\t%s\n", ms, philo->id, "is eating");
	else if (state == SLEEPING)
		printf("%ld\t%d\t%s\n", ms, philo->id, "is sleeping");
	else if (state == THINKING)
		printf("%ld\t%d\t%s\n", ms, philo->id, "is thinking");
	else if (state == DIED)
		printf("%ld\t%d\t%s\n", ms, philo->id, "is die");
	sem_post(philo->table->s_write);
}

int	print_error(char *msg)
{
	printf("%sERROR: %s.%s\n", RED, msg, NC);
	return (FAILURE);
}

int	ft_atoi(const char *s)
{
	int	num;

	num = 0;
	while (*s)
		num = num * 10 + (*s++ - '0');
	return (num);
}

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

char	*philo_sem_join(char *str, int num)
{
	char	*ret;
	int		i;

	i = 0;
	while (str[i])
		i++;
	ret = malloc((i + 4) * sizeof(char));
	i = -1;
	while (str[++i])
		ret[i] = str[i];
	while (num)
	{
		ret[i++] = num % 10 + '0';
		num /= 10;
	}
	ret[i] = 0;
	return (ret);
}
