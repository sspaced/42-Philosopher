#include "../headers/philosopher.h"

t_params init_params(int nb_philo, int ttd, int tte, int tts, int *philo_eat_list)
{
	t_params params;

	params.nb_philo = nb_philo;
	params.philo_eat_list = philo_eat_list;
	params.ttd = ttd;
	params.tte = tte;
	params.tts = tts;
	return (params);
}

t_philo	*init_philos_tab(int nb_philo, int ttd, int tte, int tts, int *philo_eat_list)
{
	int index;
	t_philo	*philos_tab;
	t_params params;

	index = 0;
	philos_tab = malloc(nb_philo * sizeof(t_philo));
	params = init_params(nb_philo, ttd, tte, tts, philo_eat_list);
	if (!philos_tab)
		return (NULL);
	while (index < nb_philo)
	{
		philos_tab[index].params = params;
		philos_tab[index].philo_id = index;
		philos_tab[index].eat_nb = 0;
		philos_tab[index].last_meal_time = 0;
		philos_tab[index].dead = 0;
		index++;
	}
	return (philos_tab);
}

void	*routine_function(void *philo)
{
	printf("Philo id : %d\n", (*(t_philo *)philo).philo_id);
}

void	start_philosopher(int nb_philo, int ttd, int tte, int tts, int *philo_eat_list)
{
	int index;
	t_philo		*philos_tab;

	philos_tab = init_philos_tab(nb_philo, ttd, tte, tts, philo_eat_list);
	index = 0;
	while (index < nb_philo)
	{
		pthread_create(&(philos_tab[index].thread), NULL, &routine_function, &(philos_tab[index]));
		index++;
	}
	index = 0;
	while(index < nb_philo)
	{
		pthread_join(philos_tab[index].thread, NULL);
		index++;
	}
}