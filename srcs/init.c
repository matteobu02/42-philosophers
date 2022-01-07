/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 19:15:06 by mbucci            #+#    #+#             */
/*   Updated: 2022/01/07 17:29:13 by mbucci           ###   ########.fr       */
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
		phi[i].str_id = ft_itoa(i + 1, env);
		phi[i].rfork = &(env->forks[i]);
		if (!i)
			phi[i].lfork = &(env->forks[env->nbr]);
		else
			phi[i].lfork = &(env->forks[i - 1]);
		if (pthread_mutex_init(&(phi[i].write), NULL))
			free_error(env);
		if (pthread_mutex_init(&(phi[i].eat), NULL))
			free_error(env);
		if (pthread_mutex_init(&(phi[i].sleep), NULL))
			free_error(env);
	}
}

void	init_threads(t_data *env)
{
	int	i;

	i = -1;
	while (++i < env->nbr)
		if (pthread_create(&(env->philos[i].thread_id),
				NULL, start_routine, (void *)env) != 0)
			free_error(env);
}
