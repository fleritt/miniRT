/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfleritt <rfleritt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:08:29 by rfleritt          #+#    #+#             */
/*   Updated: 2026/03/12 17:14:11 by rfleritt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	exit_msg_error(char *err)
{
	ft_putstr_fd(err, 2);
	exit(EXIT_FAILURE);
}

int	ft_msg_error(char *err, int ret)
{
	ft_putstr_fd(err, 2);
	return (ret);
}
