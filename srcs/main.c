/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:16:17 by mbucci            #+#    #+#             */
/*   Updated: 2022/01/08 15:35:45 by mbucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*check_args(int ac, char **args)
{
	t_data	*env;

	env = (t_data *)malloc(sizeof(t_data));
	if (!env)
		exit(EXIT_FAILURE);
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
	return (env);
}

int	main(int ac, char **av)
{
	t_data	*env;

	if (ac < 5)
	{
		printf("not enough args\n");
		return (0);
	}
	env = check_args(ac, av);
	init_forks(env);
	init_philos(env);
	manage_threads(env);
	return (0);
}
