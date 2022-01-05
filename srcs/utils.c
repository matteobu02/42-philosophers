/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 12:50:57 by mbucci            #+#    #+#             */
/*   Updated: 2022/01/05 13:09:43 by mbucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_error(t_philo *data)
{
	free(data);
	data = NULL;
	exit(EXIT_FAILURE);
}

int	ft_atoi(char *s, t_philo *data)
{
	int	n;
	int	i;

	i = 0;
	while (s[i] >= 9 && s[i] <= 13)
		i++;
	if (s[i] == '+')
		i++;
	else if (s[i++] == '-')
		free_error(data);
	n = 0;
	while (s[i])
	{
		if (s[i] > 57 || s[i] < 48)
			free_error(data);
		n = n * 10 + (s[i++] - 48);
		if (n > 2147483647)
			free_error(data);
	}
	return (n);
}
