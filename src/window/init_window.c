/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:24:55 by rfleritt          #+#    #+#             */
/*   Updated: 2026/01/29 18:48:30 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	init_window(t_data *data)
{
	if (!data)
		return ;
	data->window = malloc(sizeof(t_window));
	data->window->mlx = mlx_init(WIDTH, HEIGHT, "minirt", true);
	if (!data->window->mlx)
        return ;
	data->window->mlx_image = mlx_new_image(data->window->mlx, WIDTH, HEIGHT);
	if (!data->window->mlx_image)
		return ;
	init_camera(data);
	ft_render(data);
	mlx_image_to_window(data->window->mlx, data->window->mlx_image, 0, 0);
	mlx_key_hook(data->window->mlx, key_register, data);
	mlx_loop(data->window->mlx);
	mlx_delete_image(data->window->mlx, data->window->mlx_image);
	mlx_terminate(data->window->mlx);
}