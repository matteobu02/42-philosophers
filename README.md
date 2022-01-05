# 1. philo = tread
	1 philo = 1 thread
	
	int i = -1;
	while (++i < env->philos)
		pthread_create(&philo_tab[i], NULL, live, (void *)arg);

# 2. fork = mutex
	int	j = -1;
	pthread_mutex_t	*tab_forks = (ptread_mutex_t *)malloc(sizeof(pthread_mutex_t) * env->philos);
	while (++j < env->philos)
		pthread_mutex_init(&tab_forks[j], NULL);

	pthread_mutex_lock(&tab_forks[j]);
	//code
	pthread_mutex_unlock(&tab_forks[j]);

	int	j = -i;
	while (++j < env->philos)
		pthread_mutex_destroy(&tab_forks[j]);
