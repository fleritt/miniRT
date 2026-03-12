/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfleritt <rfleritt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 17:35:39 by rfleritt          #+#    #+#             */
/*   Updated: 2026/03/12 17:37:17 by rfleritt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_color	calculate_specular(t_light light, t_hit_info hit, t_vec3 view_dir)
{
	t_vec3	light_dir;
	t_vec3	reflect_dir;
	float	spec;
	t_color	result;
	float	shininess;

	shininess = 32.0f;
	light_dir = vec_norm(vec_sub(light.position, hit.point));
	reflect_dir = vec_sub(vec_mult(hit.normal, 2.0f * vec3_dot(hit.normal,
					light_dir)), light_dir);
	reflect_dir = vec_norm(reflect_dir);
	spec = vec3_dot(reflect_dir, view_dir);
	if (spec < 0)
		spec = 0;
	spec = pow(spec, shininess);
	result.r = (light.color.r / 255.0f) * light.intensity * spec * 255.0f;
	result.g = (light.color.g / 255.0f) * light.intensity * spec * 255.0f;
	result.b = (light.color.b / 255.0f) * light.intensity * spec * 255.0f;
	return (result);
}

t_color	calculate_lighting(t_data *data, t_hit_info hit, t_vec3 view_dir)
{
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;
	t_color	final_color;
	int		in_shadow;

	ambient = calculate_ambient(data->scene->ambient, hit.color);
	diffuse = (t_color){0, 0, 0};
	specular = (t_color){0, 0, 0};
	if (data->scene->light && data->scene->n_light > 0)
	{
		in_shadow = is_in_shadow(data, hit, data->scene->light[0]);
		if (!in_shadow)
		{
			diffuse = calculate_diffuse(data->scene->light[0], hit);
			specular = calculate_specular(data->scene->light[0], hit, view_dir);
		}
	}
	final_color = add_colors(ambient, diffuse);
	final_color = add_colors(final_color, specular);
	return (final_color);
}
