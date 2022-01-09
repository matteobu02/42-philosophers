/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 11:38:17 by mbucci            #+#    #+#             */
/*   Updated: 2022/01/09 11:53:16 by mbucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo.rfork);
	print_message();		// has taken a fork
	pthread_mutex_lock(philo.lfork);
	print_message();		// has taken a fork
	print_message();		// is eating
	ft_usleep(philo.env->time_eat);
	pthread_mutex_unlock(philo.rfork);
	pthread_mutex_unlock(philo.lfork);
}
