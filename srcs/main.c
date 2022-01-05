/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:16:17 by mbucci            #+#    #+#             */
/*   Updated: 2022/01/05 16:12:28 by mbucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*check_args(int ac, char **args)
{
	t_philo	*env;

	env = (t_philo *)malloc(sizeof(t_philo));
	if (!env)
		exit(EXIT_FAILURE);
	env->philos = ft_atoi(args[1], env);
	env->t_die = ft_atoi(args[2], env);
	env->t_eat = ft_atoi(args[3], env);
	env->t_sleep = ft_atoi(args[4], env);
	if (ac == 6)
		env->cycles = ft_atoi(args[5], env);
	return (env);
}

int	main(int ac, char **av)
{
	t_philo	*env;

	if (ac < 5)
		return (0);
	env = check_args(ac, av);
}
