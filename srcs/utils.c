/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 12:50:57 by mbucci            #+#    #+#             */
/*   Updated: 2022/01/06 13:57:56 by mbucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_error(t_data *env)
{
	free(env);
	env = NULL;
	exit(EXIT_FAILURE);
}

void	free_all(t_data *env, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < env->nbr)
	{
		free(env->philos[i].str_id);
		env->philos[i].id_str = NULL;
		free(env->philos[i]);
		free(env->forks[i]);
	}
}

int	ft_atoi(char *s, t_data *env)
{
	int	n;
	int	i;

	i = 0;
	while (s[i] >= 9 && s[i] <= 13)
		i++;
	if (s[i] == '+')
		i++;
	else if (s[i++] == '-')
		free_error(env);
	n = 0;
	while (s[i])
	{
		if (s[i] > 57 || s[i] < 48)
			free_error(env);
		n = n * 10 + (s[i++] - 48);
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

char	*ft_itoa(unsigned long n)
{
	char	*s;
	int		len;

	len = get_len_int(n);
	s = (char *)malloc(len + 1);
	if (!s)
		return (NULL);
	s[len--] = 0;
	while (n)
	{
		s[len--] = n % 10 + 48;
		n /= 10;
	}
	return (s);
}
