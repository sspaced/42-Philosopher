/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:07:35 by root              #+#    #+#             */
/*   Updated: 2024/10/02 12:02:47 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

t_params	init_params(int arg_nb, char **args)
{
	t_params	params;

	params.nb_philo = ft_atoi(args[1]);
	params.ttd = ft_atoi(args[2]);
	params.tte = ft_atoi(args[3]);
	params.tts = ft_atoi(args[4]);
	if (arg_nb == 6)
		params.max_meals = ft_atoi(args[5]);
	else
		params.max_meals = -1;
	return (params);
}

int	init_table(t_table *table, int arg_nb, char **args)
{
	table->params = init_params(arg_nb, args);
	table->dead = 0;
	table->ready = 0;
	table->start_time = 0;
	table->philo = NULL;
	if (!init_table_mutexes(table))
		return (0);
	if (!init_table_philo(table))
		return (0);
	philo_circular(table);
	return (1);
}

int	init_table_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->dead_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&table->ready_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&table->write_mutex, NULL))
		return (0);
	return (1);
}

int	init_table_philo(t_table *table)
{
	t_philo	*philo;
	int		id;

	id = 1;
	while (id <= table->params.nb_philo)
	{
		philo = philo_create_node(table, id);
		if (!philo)
			return (free_philo(table), 0);
		philo_add_back(&table->philo, philo);
		id ++;
	}
	return (1);
}
