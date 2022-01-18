/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 11:38:17 by mbucci            #+#    #+#             */
/*   Updated: 2022/01/18 17:01:47 by mbucci           ###   ########.fr       */
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

	if (philo->env->stop)
		return ;
	pthread_mutex_lock(&(philo->env->write));
	t = current_time() - philo->env->start;
	printf("%lu %d %s\n", t, philo->id, s);
	pthread_mutex_unlock(&(philo->env->write));
}

void	philo_eat(t_philo *philo)
{
	t_data	*env;

	env = philo->env;
	pthread_mutex_lock(philo->rfork);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->lfork);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(&(env->eat));
	print_message(philo, "is eating");
	philo->last_meal = current_time();
	pthread_mutex_unlock(&(env->eat));
	ft_usleep(env->time_eat);
	philo->meals += 1;
	if (philo->meals == philo->env->cycles)
		philo->env->full_philos += 1;
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
}
