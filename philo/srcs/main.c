/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:16:17 by mbucci            #+#    #+#             */
/*   Updated: 2022/01/22 13:09:23 by mbucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac, char **args, t_data *env)
{
	env->forks = NULL;
	env->philos = NULL;
	env->nbr = ft_atoi(args[1], env);
	env->time_die = ft_atoi(args[2], env);
	env->time_eat = ft_atoi(args[3], env);
	env->time_sleep = ft_atoi(args[4], env);
	if (ac == 6)
		env->cycles = ft_atoi(args[5], env);
	else
		env->cycles = 0;
	if (pthread_mutex_init(&(env->write), NULL))
		return (free_error(env));
	if (pthread_mutex_init(&(env->eat), NULL))
		return (free_error(env));
	if (env->nbr == -1 || env->time_die == -1 || env->time_eat == -1
		|| env->time_sleep == -1 || env->cycles == -1)
		return (-1);
	return (0);
}

int	exit_program(t_data *env)
{
	int	i;

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
		return (free_error(env));
	if (pthread_mutex_destroy(&(env->eat)))
		return (free_error(env));
	i = -1;
	while (++i < env->nbr)
		if (pthread_mutex_destroy(&(env->forks[i])))
			return (free_error(env));
	free(env->forks);
	env->forks = NULL;
	return (1);
}

int	main(int ac, char **av)
{
	t_data	env;

	if (ac < 5 || ac > 6)
		return (1);
	if (check_args(ac, av, &env) == -1)
		return (1);
	if (init_forks(&env) == -1)
		return (1);
	if (init_philos(&env) == -1)
		return (1);
	if (manage_threads(&env) == -1)
		return (1);
	if (exit_program(&env) == -1)
		return (1);
	return (0);
}
