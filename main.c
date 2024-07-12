/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:07:35 by root              #+#    #+#             */
/*   Updated: 2024/07/12 18:32:10 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/philosopher.h"

int	main(void)
{
	int nb_philo = 4;
	int ttd = 200000;
	int tte = 200000;
	int tts = 100000;
	int *philo_eat_list = NULL;
	
	start_philosopher(nb_philo, init_params(ttd, tte, tts, philo_eat_list));
	return (0);
}
