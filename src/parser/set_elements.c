/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 15:30:56 by rfleritt          #+#    #+#             */
/*   Updated: 2026/01/29 19:15:06 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_sphere set_sphere(char **data)
{
    t_sphere sphere;
    
    sphere.center = parse_vec(data[1]);
    sphere.radius = ft_atof(data[2]);
    sphere.color = parse_color(data[3]);
    return (sphere);
}

t_light set_light(char **data)
{
    t_light light;
    
    light.position = parse_vec(data[1]);
    light.intensity = ft_atof(data[2]);
    if (light.intensity < 0.0f || light.intensity > 1.0f)
        exit_msg_error("Intensity light just can be 0.0 - 1.0");
    light.color = parse_color(data[3]);
    return (light);
}

t_plane set_plane(char **data)
{
    t_plane plane;
    
    plane.point = parse_vec(data[1]);
    plane.normal = parse_vec(data[2]);
    if (plane.normal.x == 0 && plane.normal.y == 0 && plane.normal.z == 0)
        exit_msg_error("plane normal can't be 0,0,0");
    plane.color = parse_color(data[3]);
    return (plane);
}

t_camera set_camera(char **data)
{
    t_camera camera;
    
    camera.position = parse_vec(data[1]);
    camera.direction = parse_vec(data[2]);
    camera.pov = ft_atof(data[3]);
    if (camera.pov < 0 || camera.pov > 180)
        exit_msg_error("Camera pov needs a parameter between 0-180");
    return (camera);
}

t_ambient set_ambient(char **data)
{
    t_ambient ambient;
    
    ambient.intensity = ft_atof(data[1]);
    if (ambient.intensity < 0.0f || ambient.intensity > 1.0f)
        exit_msg_error("Intensity light just can be 0.0 - 1.0");
    ambient.color = parse_color(data[2]);
    return (ambient);
}