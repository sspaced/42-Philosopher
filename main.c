/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:07:35 by root              #+#    #+#             */
/*   Updated: 2024/07/09 02:30:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/philosopher.h"

int	main(void)
{
	int nb_philo = 4;
	int ttd = 100000;
	int tte = 200000;
	int tts = 100000;
	int *philo_eat_list = NULL;
	
	start_philosopher(nb_philo, ttd, tte, tts, philo_eat_list);
	return (0);
}

//Mutexes test
// int	main(void)
// {
// 	int *ready = malloc(sizeof(int));
// 	*ready = 0;
// 	pthread_mutex_t mutex;
// 	pthread_mutex_init(&mutex, NULL);

// 	pthread_mutex_lock(&mutex);
// 	printf("ready status : %d\n", *ready);
// 	pthread_mutex_unlock(&mutex);
// 	return (0);
// }