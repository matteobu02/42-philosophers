/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 11:38:17 by mbucci            #+#    #+#             */
/*   Updated: 2022/01/11 11:36:56 by mbucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int usec)
{
	int	i;

	i = -1;
	while (++i < usec / 2)
		usleep(500);
}

void	print_message(t_philo *philo, char *s)
{
	pthread_mutex_lock(&(philo->env->write));
	printf("time %d %s\n", philo->id, s);
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
