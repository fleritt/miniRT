/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfleritt <rfleritt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:24:55 by rfleritt          #+#    #+#             */
/*   Updated: 2025/12/22 18:22:11 by rfleritt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	init_window(t_data *data)
{
	if (!data)
		return ;
	data->window = malloc(sizeof(t_window));
	data->window->color = malloc(sizeof(t_color) * 2);
	data->window->color[0] = (t_color){135, 206, 235};
	data->window->color[1] = (t_color){25, 25, 112};
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