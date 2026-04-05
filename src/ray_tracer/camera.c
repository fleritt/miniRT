/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 16:52:19 by rfleritt          #+#    #+#             */
/*   Updated: 2026/04/05 17:08:50 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	init_camera(t_data *data)
{
	t_vec3	world_up;
	t_vec3	forward;

	forward = vec_norm(data->scene->camera.direction);
	data->scene->camera.forward = forward;
	world_up = (t_vec3){0, 1, 0};
	if (fabs(vec3_dot(forward, world_up)) > 0.999f)
		world_up = (t_vec3){0, 0, 1};
	data->scene->camera.right = vec_norm(vec_cross(forward, world_up));
	data->scene->camera.up = vec_norm(vec_cross(data->scene->camera.right,
				forward));
}
