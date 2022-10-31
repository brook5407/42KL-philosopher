/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:29:18 by chchin            #+#    #+#             */
/*   Updated: 2022/10/31 15:29:19 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine_take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->left);
	print_status(philo, "has taken a fork");
}

//void	routine_eat(t_philo *philo)
//{
//
//}