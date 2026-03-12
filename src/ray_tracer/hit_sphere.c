/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfleritt <rfleritt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 16:50:07 by rfleritt          #+#    #+#             */
/*   Updated: 2026/03/12 17:29:24 by rfleritt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static float	solve_quadratic(float a, float half_b, float discriminant)
{
	float	sqrt_d;
	float	t;

	sqrt_d = sqrtf(discriminant);
	t = (-half_b - sqrt_d) / a;
	if (t > 0.001f)
		return (t);
	t = (-half_b + sqrt_d) / a;
	if (t > 0.001f)
		return (t);
	return (-1.0f);
}

float	hit_sphere(t_ray ray, t_sphere sphere)
{
	t_vec3	oc;
	float	a;
	float	half_b;
	float	c;

	oc = vec_sub(ray.origin, sphere.center);
	a = vec3_dot(ray.direction, ray.direction);
	half_b = vec3_dot(oc, ray.direction);
	c = vec3_dot(oc, oc) - sphere.radius * sphere.radius;
	if (half_b * half_b - a * c < 0)
		return (-1.0f);
	return (solve_quadratic(a, half_b, half_b * half_b - a * c));
}

int	hit_sphere_info(t_ray ray, t_sphere sphere, t_hit_info *hit)
{
	float	t;

	t = hit_sphere(ray, sphere);
	if (t < 0)
		return (0);
	hit->t = t;
	hit->point = vec_add(ray.origin, vec_mult(ray.direction, t));
	hit->normal = vec_norm(vec_sub(hit->point, sphere.center));
	hit->color = sphere.color;
	return (1);
}

void	init_hit_sphere(int x, int y, t_data *data)
{
	float	scale;
	float	aspect_ratio;
	float	px;
	float	py;
	t_vec3	ray_dir;

	aspect_ratio = (float)WIDTH / (float)HEIGHT;
	scale = tan((data->scene->camera.pov * M_PI / 180.0f) / 2.0f);
	px = (2.0f * ((x + 0.5f) / WIDTH) - 1.0f) * aspect_ratio * scale;
	py = (1.0f - 2.0f * ((y + 0.5f) / HEIGHT)) * scale;
	ray_dir = data->scene->camera.forward;
	ray_dir = vec_add(ray_dir, vec_mult(data->scene->camera.right, px));
	ray_dir = vec_add(ray_dir, vec_mult(data->scene->camera.up, py));
	data->ray.origin = data->scene->camera.position;
	data->ray.direction = vec_norm(ray_dir);
}
