/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 11:38:17 by mbucci            #+#    #+#             */
/*   Updated: 2022/01/11 22:02:49 by mbucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int msec)
{
	unsigned long	t;

	t = current_time();
	while (current_time() < t + msec)
		usleep(10);
}

void	print_message(t_philo *philo, char *s)
{
	unsigned long	t;

	t = current_time() - philo->env->start;
	pthread_mutex_lock(&(philo->env->write));
	printf("%lu %d %s\n", t, philo->id, s);
	pthread_mutex_unlock(&(philo->env->write));
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->rfork);
	print_message(philo, "has taken a fork");
	if (philo->lfork)
	{
		pthread_mutex_lock(philo->lfork);
		print_message(philo, "has taken a fork");
		print_message(philo, "is eating");
		ft_usleep(philo->env->time_eat);
		pthread_mutex_unlock(philo->lfork);
		if (philo->env->cycles)
			philo->meals += 1;
	}
	pthread_mutex_unlock(philo->rfork);
}
