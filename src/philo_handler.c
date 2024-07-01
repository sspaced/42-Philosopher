/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 23:21:52 by root              #+#    #+#             */
/*   Updated: 2024/07/01 23:29:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

void	*routine_function(void *philo)
{
	// Try to lock 2 forks out of a list of all forks.
		// Display thinking
	// if succed to lock 2 fork
		// Wait the tte amount
		// Change last_meal_time to current time
		// wait tts amount
	printf("Philo id : %d\n", (*(t_philo *)philo).philo_id);
}

void	start_philosopher(int nb_philo, int ttd, int tte, int tts, int *philo_eat_list)
{
	int index;
	t_philo		*philos_tab;
	
	//create philos_nb + 1 thread to monitor death
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
