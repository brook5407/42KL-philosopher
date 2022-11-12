/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brook <brook@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:40:37 by brook             #+#    #+#             */
/*   Updated: 2022/11/09 23:23:10 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:39:37 by chchin            #+#    #+#             */
/*   Updated: 2022/11/07 22:39:22 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

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
	ret[i] = (num / 100) + '0';
	ret[++i] = (num / 10 % 10) + '0';
	ret[++i] = (num % 10) + '0';
	ret[++i] = 0;
	return (ret);
}

int	print_error(char *msg)
{
	printf("%sERROR: %s.%s\n", RED, msg, NC);
	return (FAILURE);
}

void	print_status(t_philo *philo, t_state state)
{
	int	time;

	time = (int)get_timestamp(philo->info);
	sem_wait(philo->info->s_write);
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
	sem_post(philo->info->s_write);
}
