/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 12:50:57 by mbucci            #+#    #+#             */
/*   Updated: 2022/01/08 15:45:39 by mbucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_error(t_data *env)
{
	int	i;

	printf("error\n");
	i = -1;
	if (env->philos)
	{
		while (++i < env->nbr)
		{
			if (env->philos[i].str_id)
				free(env->philos[i].str_id);
			env->philos[i].str_id = NULL;
			env->philos[i].rfork = NULL;
			env->philos[i].lfork = NULL;
			env->philos[i].env = NULL;
			pthread_mutex_destroy(&(env->philos[i].sleep));
			pthread_mutex_destroy(&(env->philos[i].eat));
		}
		free(env->philos);
	}
	env->philos = NULL;
	i = -1;
	if (env->forks)
	{
		while (++i < env->nbr)
			if (pthread_mutex_destroy(&(env->forks[i])))
				free_error(env);
		free(env->forks);
	}
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

int	get_len_int(unsigned long n)
{
	int	ret;

	ret = 0;
	if (!n)
		return (1);
	while (n)
	{
		n /= 10;
		ret++;
	}
	return (ret);
}

char	*ft_itoa(unsigned long n, t_data *env)
{
	char	*s;
	int		len;

	len = get_len_int(n);
	s = (char *)malloc(len + 1);
	if (!s)
		free_error(env);
	s[len--] = 0;
	while (n)
	{
		s[len--] = n % 10 + 48;
		n /= 10;
	}
	return (s);
}
