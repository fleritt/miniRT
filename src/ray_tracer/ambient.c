/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 12:10:09 by ricardo           #+#    #+#             */
/*   Updated: 2026/02/07 17:39:28 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_color	calculate_ambient(t_ambient ambient, t_color object_color)
{
	t_color	result;

	result.r = (ambient.color.r / 255.0f) * ambient.intensity * object_color.r;
	result.g = (ambient.color.g / 255.0f) * ambient.intensity * object_color.g;
	result.b = (ambient.color.b / 255.0f) * ambient.intensity * object_color.b;
	if (result.r > 255.0f)
		result.r = 255.0f;
	if (result.g > 255.0f)
		result.g = 255.0f;
	if (result.b > 255.0f)
		result.b = 255.0f;
	return (result);
}

t_color	calculate_diffuse(t_light light, t_hit_info hit)
{
	t_vec3	light_dir;
	float	diff;
	t_color	result;

	// Vector desde el punto de impacto hacia la luz
	light_dir = vec_norm(vec_sub(light.position, hit.point));
	
	// Producto punto entre normal y dirección de luz (ángulo de incidencia)
	diff = vec3_dot(hit.normal, light_dir);
	
	// Si es negativo, la luz está detrás de la superficie
	if (diff < 0)
		diff = 0;
	
	// Aplicar intensidad de luz y color
	result.r = (light.color.r / 255.0f) * light.intensity * diff * hit.color.r;
	result.g = (light.color.g / 255.0f) * light.intensity * diff * hit.color.g;
	result.b = (light.color.b / 255.0f) * light.intensity * diff * hit.color.b;
	
	return (result);
}

t_color	add_colors(t_color c1, t_color c2)
{
	t_color	result;

	result.r = c1.r + c2.r;
	result.g = c1.g + c2.g;
	result.b = c1.b + c2.b;
	
	// Clamp a 255
	if (result.r > 255.0f)
		result.r = 255.0f;
	if (result.g > 255.0f)
		result.g = 255.0f;
	if (result.b > 255.0f)
		result.b = 255.0f;
	
	return (result);
}

