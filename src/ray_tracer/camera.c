/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfleritt <rfleritt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 16:52:19 by rfleritt          #+#    #+#             */
/*   Updated: 2025/12/22 18:21:53 by rfleritt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void init_camera(t_data *data)
{
    t_vec3 world_up;

    data->camera.position = (t_vec3){0, 0, -2};
    data->camera.direction = (t_vec3){0, 0, 1};
    data->camera.pov = 100.0f;
    data->camera.forward = vec_norm(data->camera.direction);
    world_up = (t_vec3){0, 1, 0};
    data->camera.right = vec_norm(vec_cross(data->camera.forward, world_up));
    data->camera.up = vec_cross(data->camera.right, data->camera.forward);
}