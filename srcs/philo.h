/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:18:29 by mbucci            #+#    #+#             */
/*   Updated: 2022/01/08 14:31:40 by mbucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

struct	s_data;

typedef struct s_philo
{
	int				id;
	char			*str_id;
	pthread_t		thread_id;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	eat;
	pthread_mutex_t	sleep;
	struct s_data	*env;
}	t_philo;

typedef struct s_data
{
	int				nbr;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				cycles;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
}	t_data;

void	free_error(t_data *env);
int		ft_atoi(char *s, t_data *env);
char	*ft_itoa(unsigned long n, t_data *env);

void	init_forks(t_data *env);
void	init_philos(t_data *env);
void	manage_threads(t_data *env);

#endif
