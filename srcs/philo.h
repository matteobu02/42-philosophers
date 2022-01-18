/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:18:29 by mbucci            #+#    #+#             */
/*   Updated: 2022/01/17 20:08:19 by mbucci           ###   ########.fr       */
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
	pthread_t		thread_id;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
	int				meals;
	unsigned long	last_meal;
	struct s_data	*env;
}	t_philo;

typedef struct s_data
{
	int				nbr;
	unsigned int	time_die;
	int				time_eat;
	int				time_sleep;
	int				cycles;
	int				full_philos;
	int				stop;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	unsigned long	start;
}	t_data;

void			free_error(t_data *env);
int				ft_atoi(char *s, t_data *env);
char			*ft_itoa(unsigned long n, t_data *env);
unsigned long	current_time(void);

void			init_forks(t_data *env);
void			init_philos(t_data *env);
void			manage_threads(t_data *env);
void			exit_program(t_data *env);

void			ft_usleep(int msec);
void			print_message(t_philo *philo, char *s);
void			philo_eat(t_philo *philo);

#endif
