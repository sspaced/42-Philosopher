/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:07:35 by root              #+#    #+#             */
/*   Updated: 2024/10/02 16:42:38 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

int	ft_isdigit(int c)
{
	if (c <= '9' && c >= '0')
	{
		return (2048);
	}
	return (0);
}

int	check_if_digit(int arg_nb, char **args)
{
	int	i;
	int	u;

	i = 1;
	u = 1;
	while (i < arg_nb)
	{
		while (args[i][u])
		{
			if (!ft_isdigit(args[i][u]))
				return (0);
			u++;
		}
		u = 0;
		i++;
	}
	return (1);
}

int	check_arg(int arg_nb, char **args)
{
	int	i;

	i = 1;
	if (arg_nb <= 4 || arg_nb > 6)
		return (ft_putstr_fd("Invalid argument : arg number !\n", 2), 0);
	if (!check_if_digit(arg_nb, args))
		return (ft_putstr_fd("Invalid argument : not number !\n", 2), 0);
	while (i < arg_nb)
	{
		if (i != 1 && i != 5 && ft_atoi(args[i]) < 60)
			return (ft_putstr_fd("Invalid argument : time to low !\n", 2), 0);
		if (i == 5 && ft_atoi(args[i]) <= 0)
			return (ft_putstr_fd("Invalid argument : not enough meal !\n", 2),
				0);
		if (i == 1 && ft_atoi(args[i]) <= 0)
			return (ft_putstr_fd("Invalid argument : not enough philos !\n", 2),
				0);
		if (i == 1 && ft_atoi(args[i]) > 200)
			return (ft_putstr_fd("Invalid argument : too much philos !\n", 2),
				0);
		i++;
	}
	return (1);
}

static const char	*ft_white_space(const char *str)
{
	while (((*str >= 9) && (*str <= 13)) || (*str == 32))
		str++;
	return (str);
}

int	ft_atoi(const char *str)
{
	size_t	sign;
	long	nb;

	nb = 0;
	sign = 0;
	str = ft_white_space(str);
	if (*str == '-')
	{
		sign++;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (((nb * 10) + (*str - 48)) / 10 != nb)
			return (LONG_MIN * (sign > 0) + LONG_MAX * (sign == 0));
		nb = (nb * 10) + (*str - 48);
		str++;
	}
	if (sign == 1)
		return (-nb);
	if (sign > 1)
		return (0);
	return ((int)nb);
}
