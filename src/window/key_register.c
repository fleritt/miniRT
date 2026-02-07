/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_register.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:52:31 by rfleritt          #+#    #+#             */
/*   Updated: 2026/02/07 18:25:25 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void close_window(void *param)
{
	t_data *data;

	data = (t_data *)param;
	mlx_close_window(data->window->mlx);
}

void key_register(mlx_key_data_t keydata, void *param)
{
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		close_window(param);
}