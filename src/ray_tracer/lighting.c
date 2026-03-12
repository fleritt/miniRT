/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfleritt <rfleritt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:30:00 by ricardo           #+#    #+#             */
/*   Updated: 2026/03/12 17:36:14 by rfleritt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static t_ray	build_shadow_ray(t_hit_info hit, t_light light, float *dist)
{
	t_ray	shadow_ray;
	t_vec3	light_dir;

	light_dir = vec_sub(light.position, hit.point);
	*dist = vec_length(light_dir);
	shadow_ray.origin = vec_add(hit.point, vec_mult(hit.normal, 0.001f));
	shadow_ray.direction = vec_norm(light_dir);
	return (shadow_ray);
}

static int	shadow_spheres(t_data *data, t_ray ray, float dist)
{
	float	t;
	int		i;

	i = 0;
	while (i < data->scene->n_sphere)
	{
		t = hit_sphere(ray, data->scene->sphere[i]);
		if (t > 0.001f && t < dist)
			return (1);
		i++;
	}
	return (0);
}

static int	shadow_planes(t_data *data, t_ray ray, float dist)
{
	float	t;
	int		i;

	i = 0;
	while (i < data->scene->n_plane)
	{
		t = hit_plane(ray, data->scene->plane[i]);
		if (t > 0.001f && t < dist)
			return (1);
		i++;
	}
	return (0);
}

static int	shadow_cylinders(t_data *data, t_ray ray, float dist)
{
	t_hit_info	hit;
	int			i;

	i = 0;
	while (i < data->scene->n_cylinder)
	{
		if (hit_cylinder_info(ray, data->scene->cylinder[i], &hit))
			if (hit.t > 0.001f && hit.t < dist)
				return (1);
		i++;
	}
	return (0);
}

int	is_in_shadow(t_data *data, t_hit_info hit, t_light light)
{
	t_ray	shadow_ray;
	float	light_distance;

	shadow_ray = build_shadow_ray(hit, light, &light_distance);
	if (shadow_spheres(data, shadow_ray, light_distance))
		return (1);
	if (shadow_planes(data, shadow_ray, light_distance))
		return (1);
	if (shadow_cylinders(data, shadow_ray, light_distance))
		return (1);
	return (0);
}
