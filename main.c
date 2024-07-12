/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:07:35 by root              #+#    #+#             */
/*   Updated: 2024/07/12 18:39:19 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/philosopher.h"

int	main(void)
{
	int	nb_philo;
	int	ttd;
	int	tte;
	int	tts;
	int	*philo_eat_list;

	nb_philo = 4;
	ttd = 200000;
	tte = 200000;
	tts = 100000;
	philo_eat_list = NULL;
	start_philosopher(nb_philo, init_params(ttd, tte, tts, philo_eat_list));
	return (0);
}
