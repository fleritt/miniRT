/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:00:00 by ricardo           #+#    #+#             */
/*   Updated: 2026/04/05 16:25:33 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static int	check_bottom_cap(t_ray ray, t_cylinder cy, t_hit_info *hit)
{
	float	t;
	float	denom;
	float	dist;
	t_vec3	point;

	denom = vec3_dot(ray.direction, cy.axis);
	if (fabs(denom) <= 1e-6)
		return (0);
	t = vec3_dot(vec_sub(cy.center, ray.origin), cy.axis) / denom;
	if (t <= 0.001f)
		return (0);
	point = vec_add(ray.origin, vec_mult(ray.direction, t));
	dist = vec_length(vec_sub(point, cy.center));
	if (dist > cy.radius)
		return (0);
	hit->t = t;
	hit->point = point;
	hit->normal = vec_mult(cy.axis, -1);
	hit->color = cy.color;
	if (vec3_dot(hit->normal, ray.direction) > 0)
    	hit->normal = vec_mult(hit->normal, -1);
	return (1);
}

static int	check_top_cap(t_ray ray, t_cylinder cy, t_hit_info *hit)
{
	float	t;
	float	denom;
	float	dist;
	t_vec3	point;
	t_vec3	top;

	top = vec_add(cy.center, vec_mult(cy.axis, cy.height));
	denom = vec3_dot(ray.direction, cy.axis);
	if (fabs(denom) <= 1e-6)
		return (0);
	t = vec3_dot(vec_sub(top, ray.origin), cy.axis) / denom;
	if (t <= 0.001f)
		return (0);
	point = vec_add(ray.origin, vec_mult(ray.direction, t));
	dist = vec_length(vec_sub(point, top));
	if (dist > cy.radius)
		return (0);
	hit->t = t;
	hit->point = point;
	hit->normal = cy.axis;
	hit->color = cy.color;
	if (vec3_dot(hit->normal, ray.direction) > 0)
    	hit->normal = vec_mult(hit->normal, -1);
	return (1);
}

int	hit_cylinder_caps(t_ray ray, t_cylinder cy, t_hit_info *hit)
{
	if (check_bottom_cap(ray, cy, hit))
		return (1);
	if (check_top_cap(ray, cy, hit))
		return (1);
	return (0);
}

float	cylinder_disc(t_ray ray, t_cylinder cy, float *a, float *b)
{
	float	c;
	t_vec3	oc;

	oc = vec_sub(ray.origin, cy.center);
	*a = vec3_dot(ray.direction, ray.direction)
		- pow(vec3_dot(ray.direction, cy.axis), 2);
	*b = 2 * (vec3_dot(ray.direction, oc)
			- vec3_dot(ray.direction, cy.axis)
			* vec3_dot(oc, cy.axis));
	c = vec3_dot(oc, oc)
		- pow(vec3_dot(oc, cy.axis), 2)
		- cy.radius * cy.radius;
	return (*b * *b - 4 * *a * c);
}

int	fill_cyl(t_ray ray, t_cylinder cy, float t, t_hit_info *hit)
{
	float	height_proj;
	t_vec3	point;
	t_vec3	normal;

	point = vec_add(ray.origin, vec_mult(ray.direction, t));
	height_proj = vec3_dot(vec_sub(point, cy.center), cy.axis);
	if (height_proj < 0 || height_proj > cy.height)
		return (0);
	normal = vec_sub(vec_sub(point, cy.center),
			vec_mult(cy.axis, height_proj));
	normal = vec_norm(normal);
	hit->t = t;
	hit->point = point;
	hit->normal = normal;
	hit->color = cy.color;
	if (vec3_dot(hit->normal, ray.direction) > 0)
		hit->normal = vec_mult(hit->normal, -1);
	return (1);
}
