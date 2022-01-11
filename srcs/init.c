/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 19:15:06 by mbucci            #+#    #+#             */
/*   Updated: 2022/01/11 01:11:22 by mbucci           ###   ########.fr       */
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
		phi[i].rfork = &(env->forks[i]);
		phi[i].env = env;
		if (env->cycles)
			phi[i].meals = 0;
		else
			phi[i].meals = -1;
		if (!i)
			phi[i].lfork = &(env->forks[env->nbr]);
		else
			phi[i].lfork = &(env->forks[i - 1]);
	}
}

void	*start_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (philo->meals < philo->env->cycles)
	{
		philo_eat(philo);
		if (philo->meals < philo->env->cycles)
		{
			print_message(philo, "is sleeping");
			ft_usleep(philo->env->time_sleep);
			print_message(philo, "is thinking");
		}
	}
	return (NULL);
}

void	manage_threads(t_data *env)
{
	int		i;

	i = -1;
	while (++i < env->nbr)
	{
		if (pthread_create(&env->philos[i].thread_id,
				NULL, start_routine, &(env->philos[i])))
			free_error(env);
	}
	i = -1;
	while (++i < env->nbr)
		if (pthread_join(env->philos[i].thread_id, NULL))
			free_error(env);
	i = -1;
	while (++i < env->nbr)
	{
		env->philos[i].rfork = NULL;
		env->philos[i].lfork = NULL;
		env->philos[i].env = NULL;
	}
	free(env->philos);
	env->philos = NULL;
	if (pthread_mutex_destroy(&(env->write)))
		free_error(env);
	i = -1;
	while (++i < env->nbr)
		if (pthread_mutex_destroy(&(env->forks[i])))
			free_error(env);
	free(env->forks);
	env->forks = NULL;
	free(env);
	env = NULL;
}
