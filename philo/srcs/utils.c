/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 12:50:57 by mbucci            #+#    #+#             */
/*   Updated: 2022/01/22 12:48:05 by mbucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_error(t_data *env)
{
	int	i;

	i = -1;
	while (env->philos && ++i < env->nbr)
		env->philos[i].env = NULL;
	free(env->philos);
	env->philos = NULL;
	i = -1;
	while (env->forks && ++i < env->nbr)
		if (pthread_mutex_destroy(&(env->forks[i])))
			return (free_error(env));
	free(env->forks);
	env->forks = NULL;
	return (-1);
}

int	ft_atoi(char *s, t_data *env)
{
	int	n;
	int	i;

	i = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '+')
		i++;
	else if (s[i] == '-')
		return (free_error(env));
	n = 0;
	while (s[i])
	{
		if (s[i] > 57 || s[i] < 48)
			return (free_error(env));
		n = (n * 10) + (s[i++] - 48);
		if (n > 2147483647)
			return (free_error(env));
	}
	if (!n)
		return (free_error(env));
	return (n);
}

unsigned long	current_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (1000 * t.tv_sec + t.tv_usec / 1000);
}
