/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:07:35 by root              #+#    #+#             */
/*   Updated: 2024/10/02 11:31:33 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		ft_putchar_fd(*s++, fd);
	}
}

int	display_info(t_philo *philo, char *info)
{
	pthread_mutex_lock(&philo->table->write_mutex);
	if (get_dead(philo))
		return (pthread_mutex_unlock(&philo->table->write_mutex), 0);
	printf("%ld %u %s\n", (current_time_ms() - philo->table->start_time),
		philo->id, info);
	pthread_mutex_unlock(&philo->table->write_mutex);
	return (1);
}

void	display_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write_mutex);
	printf("%ld %u died\n", (current_time_ms() - philo->table->start_time),
		philo->id);
	pthread_mutex_unlock(&philo->table->write_mutex);
}
