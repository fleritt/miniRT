/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_register.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:52:31 by rfleritt          #+#    #+#             */
/*   Updated: 2026/01/29 18:23:57 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void ft_reload_window(t_order key, t_data *data)
{
    t_vec3 world_up;
    
    if(key == UP)
    {
        data->scene->camera.position.y++;
        ft_render(data);
    }
    if(key == DOWN)
    {
        data->scene->camera.position.y--;
        ft_render(data);
    }
    if(key == LEFT)
    {
        data->scene->camera.position.x--;
        ft_render(data);
    }
    if(key == RIGHT)
    {
        data->scene->camera.position.x++;
        ft_render(data);
    }
    if(key == A)
    {
        data->scene->camera.direction.x++;
        data->scene->camera.forward = vec_norm(data->scene->camera.direction);
        world_up = (t_vec3){0, 1, 0};
        data->scene->camera.right = vec_norm(vec_cross(data->scene->camera.forward, world_up));
        data->scene->camera.up = vec_cross(data->scene->camera.right, data->scene->camera.forward);
        ft_render(data);
    }
    if(key == D)
    {
        data->scene->camera.direction.x--;
        data->scene->camera.forward = vec_norm(data->scene->camera.direction);
        world_up = (t_vec3){0, 1, 0};
        data->scene->camera.right = vec_norm(vec_cross(data->scene->camera.forward, world_up));
        data->scene->camera.up = vec_cross(data->scene->camera.right, data->scene->camera.forward);
        ft_render(data);
    }
}

void close_window(void)
{
    exit(1);
}

void key_register(mlx_key_data_t keydata, void *param)
{
    if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
        ft_reload_window(UP, param);
    if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
        ft_reload_window(DOWN, param);
    if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
        ft_reload_window(RIGHT, param);
    if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
        ft_reload_window(LEFT, param);
    if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
        ft_reload_window(A, param);
    if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
        ft_reload_window(D, param);
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		close_window();
}