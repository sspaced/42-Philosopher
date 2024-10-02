/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:07:35 by root              #+#    #+#             */
/*   Updated: 2024/10/02 16:31:41 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/philosopher.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (!check_arg(argc, argv))
		return (0);
	if (!init_table(&table, argc, argv))
		return (destroy_mutexes(&table), free_philo(&table), 0);
	if (!start_threads(&table))
		return (destroy_mutexes(&table), free_philo(&table), 0);
	if (!join_threads(&table))
		return (destroy_mutexes(&table), free_philo(&table), 0);
	destroy_mutexes(&table);
	free_philo(&table);
	return (0);
}
