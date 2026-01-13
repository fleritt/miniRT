/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfleritt <rfleritt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 14:18:54 by rfleritt          #+#    #+#             */
/*   Updated: 2026/01/13 14:02:39 by rfleritt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void parse_scene(t_data *data)
{
    data->scene = malloc(sizeof(t_scene_data));
    parse_ambient(data);
    parse_camera(data);
    parse_light(data);
    parse_plane(data);
    parse_sphere(data);
}