/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:07:35 by root              #+#    #+#             */
/*   Updated: 2024/09/25 17:52:13 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/philosopher.h"

int	main(int argc, char **argv)
{
	int	nb_philo;
	int	ttd;
	int	tte;
	int	tts;
	int	*philo_eat_list;
	
	if (argc < 5)
		return (printf("Invalid parameters !\n"));
	else
	{
		nb_philo = atoi(argv[1]);
		ttd = atoi(argv[2]);
		tte = atoi(argv[3]);
		tts = atoi(argv[4]);
		philo_eat_list = NULL;
		start_philosopher(nb_philo, init_params(ttd, tte, tts, philo_eat_list));	
	}
	return (0);
}
