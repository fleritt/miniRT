/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfleritt <rfleritt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:08:27 by rfleritt          #+#    #+#             */
/*   Updated: 2026/01/13 12:21:17 by rfleritt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_atof(char *str)
{
	int		i;
	int		sign;
	float	res;
	float	div;

	i = 0;
	sign = 1;
	res = 0;
	div = 1;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	if (str[i] == '.')
		while (str[++i] >= '0' && str[i] <= '9')
		{
			res = res * 10 + (str[i] - '0');
			div *= 10;
		}
	return (sign * res / div);
}

