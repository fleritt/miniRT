/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:08:29 by rfleritt          #+#    #+#             */
/*   Updated: 2026/04/05 16:37:17 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	exit_msg_error(char *err)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(err, 2);
	exit(EXIT_FAILURE);
}

int	ft_msg_error(char *err, int ret)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(err, 2);
	return (ret);
}
