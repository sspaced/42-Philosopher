/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:07:35 by root              #+#    #+#             */
/*   Updated: 2024/10/02 10:32:31 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

t_philo	*philo_last(t_philo *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (!(*lst).next)
			return (lst);
		lst = (*lst).next;
	}
	return (lst);
}

void	philo_add_back(t_philo **lst, t_philo *new)
{
	t_philo	*add;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		add = philo_last(*lst);
		(*add).next = new;
	}
	else
		*lst = new;
}

void	philo_circular(t_table *table)
{
	t_philo	*philo_head;
	t_philo	*philo_next;

	philo_head = table->philo;
	while (table->philo->next)
	{
		philo_next = table->philo->next;
		table->philo = philo_next;
	}
	table->philo->next = philo_head;
	table->philo = philo_head;
}

t_philo	*philo_create_node(t_table *table, int id)
{
	t_philo	*new_node;

	new_node = malloc(sizeof(t_philo));
	if (!new_node)
		return (NULL);
	if (pthread_mutex_init(&new_node->fork_mutex, NULL))
		return (free(new_node), NULL);
	if (pthread_mutex_init(&new_node->meals_mutex, NULL))
		return (free(new_node), NULL);
	if (pthread_mutex_init(&new_node->last_meals_mutex, NULL))
		return (free(new_node), NULL);
	if (pthread_mutex_init(&new_node->philo_state_mutex, NULL))
		return (free(new_node), NULL);
	new_node->id = id;
	new_node->philo_state = 0;
	new_node->last_meal_time = current_time_ms();
	new_node->fork_state = 0;
	new_node->meals_count = 0;
	new_node->table = table;
	new_node->next = NULL;
	return (new_node);
}
