/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 12:50:57 by mbucci            #+#    #+#             */
/*   Updated: 2022/01/12 13:32:35 by mbucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_error(t_data *env)
{
	int	i;

	i = -1;
	while (env->philos && ++i < env->nbr)
	{
		env->philos[i].rfork = NULL;
		env->philos[i].lfork = NULL;
		env->philos[i].env = NULL;
	}
	free(env->philos);
	env->philos = NULL;
	i = -1;
	while (env->forks && ++i < env->nbr)
		if (pthread_mutex_destroy(&(env->forks[i])))
			free_error(env);
	free(env->forks);
	env->forks = NULL;
	free(env);
	env = NULL;
	exit(EXIT_FAILURE);
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
		free_error(env);
	n = 0;
	while (s[i])
	{
		if (s[i] > 57 || s[i] < 48)
			free_error(env);
		n = (n * 10) + (s[i++] - 48);
		if (n > 2147483647)
			free_error(env);
	}
	return (n);
}

unsigned long	current_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (1000 * t.tv_sec + t.tv_usec / 1000);
}
