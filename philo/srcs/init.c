/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 19:15:06 by mbucci            #+#    #+#             */
/*   Updated: 2022/01/19 21:38:36 by mbucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_data *env)
{
	int	i;

	env->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * env->nbr);
	if (!env->forks)
		free_error(env);
	i = -1;
	while (++i < env->nbr)
		if (pthread_mutex_init(&(env->forks[i]), NULL))
			free_error(env);
}

void	init_philos(t_data *env)
{
	int		i;
	t_philo	*phi;

	env->philos = (t_philo *)malloc(sizeof(t_philo) * env->nbr);
	if (!env->philos)
		free_error(env);
	i = -1;
	phi = env->philos;
	while (++i < env->nbr)
	{
		phi[i].id = i + 1;
		phi[i].env = env;
		phi[i].last_meal = current_time();
		phi[i].meals = 0;
		phi[i].rfork = &(env->forks[i]);
		if (!i)
			phi[i].lfork = &(env->forks[env->nbr - 1]);
		else
			phi[i].lfork = &(env->forks[i - 1]);
	}
}

void	*start_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->env->nbr == 1)
	{
		print_message(philo, "has taken a fork");
		ft_usleep(philo->env->time_die);
		return (NULL);
	}
	if (philo->id % 2 != 0)
		ft_usleep(2);
	while (!philo->env->stop && !philo->env->full)
	{
		philo_eat(philo);
		print_message(philo, "is sleeping");
		ft_usleep(philo->env->time_sleep);
		print_message(philo, "is thinking");
	}
	return (NULL);
}

void	monitor_threads(t_data *env)
{
	int	i;

	while (!env->full)
	{
		i = -1;
		while (++i < env->nbr && !env->stop)
		{
			pthread_mutex_lock(&(env->eat));
			if (current_time() - env->philos[i].last_meal > env->time_die)
			{
				print_message(&(env->philos[i]), "died");
				pthread_mutex_lock(&(env->write));
				env->stop = 1;
			}
			pthread_mutex_unlock(&(env->eat));
		}
		if (env->stop)
			break ;
		i = 0;
		while (env->cycles && i < env->nbr && env->philos[i].meals >= env->cycles)
			i++;
		env->full = (i == env->nbr);
	}
}

void	manage_threads(t_data *env)
{
	int		i;

	env->start = current_time();
	env->stop = 0;
	i = -1;
	while (++i < env->nbr)
		if (pthread_create(&env->philos[i].thread_id,
				NULL, start_routine, &(env->philos[i])))
			free_error(env);
	monitor_threads(env);
	pthread_mutex_unlock(&(env->write));
	i = -1;
	while (++i < env->nbr)
		if (pthread_join(env->philos[i].thread_id, NULL))
			free_error(env);
}
