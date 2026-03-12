/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfleritt <rfleritt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:00:00 by ricardo           #+#    #+#             */
/*   Updated: 2026/03/12 17:25:59 by rfleritt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

float	hit_plane(t_ray ray, t_plane plane)
{
	float	denom;
	float	t;
	t_vec3	p_to_o;

	plane.normal = vec_norm(plane.normal);
	denom = vec3_dot(plane.normal, ray.direction);
	if (fabs(denom) < 1e-6)
		return (-1.0f);
	p_to_o = vec_sub(plane.point, ray.origin);
	t = vec3_dot(p_to_o, plane.normal) / denom;
	if (t < 0)
		return (-1.0f);
	return (t);
}

int	hit_plane_info(t_ray ray, t_plane plane, t_hit_info *hit)
{
	float	t;

	t = hit_plane(ray, plane);
	if (t < 0)
		return (0);
	hit->t = t;
	hit->point = vec_add(ray.origin, vec_mult(ray.direction, t));
	hit->normal = vec_norm(plane.normal);
	hit->color = plane.color;
	if (vec3_dot(hit->normal, ray.direction) > 0)
	{
		hit->normal.x = -hit->normal.x;
		hit->normal.y = -hit->normal.y;
		hit->normal.z = -hit->normal.z;
	}
	return (1);
}
