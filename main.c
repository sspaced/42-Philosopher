/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:07:35 by root              #+#    #+#             */
/*   Updated: 2024/07/01 23:09:39 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/philosopher.h"

int	main(void)
{
	int nb_philo = 4;
	int ttd = 10;
	int tte = 10;
	int tts = 2;
	int *philo_eat_list = NULL;
	
	start_philosopher(nb_philo, ttd, tte, tts, philo_eat_list);
	return (0);
}