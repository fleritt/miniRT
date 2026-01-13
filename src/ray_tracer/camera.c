/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfleritt <rfleritt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 16:52:19 by rfleritt          #+#    #+#             */
/*   Updated: 2026/01/13 14:06:50 by rfleritt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void init_camera(t_data *data)
{
    t_vec3 world_up;

    data->scene->camera.forward = vec_norm(data->scene->camera.direction);
    world_up = (t_vec3){0, 1, 0};
    data->scene->camera.right = vec_norm(vec_cross(data->scene->camera.forward, world_up));
    data->scene->camera.up = vec_cross(data->scene->camera.right, data->scene->camera.forward);
}