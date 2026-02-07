/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:00:00 by ricardo           #+#    #+#             */
/*   Updated: 2026/02/07 17:46:08 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * Intersección rayo-plano
 * Ecuación del plano: dot(normal, point - plane_point) = 0
 * Ecuación del rayo: point = origin + t * direction
 * 
 * Resolviendo:
 * t = dot(normal, plane_point - ray_origin) / dot(normal, ray_direction)
 */
float	hit_plane(t_ray ray, t_plane plane)
{
	float	denom;
	float	t;
	t_vec3	p_to_o;

	// Normalizar la normal del plano (por si acaso)
	plane.normal = vec_norm(plane.normal);
	
	// Denominador: dot(normal, ray_direction)
	denom = vec3_dot(plane.normal, ray.direction);
	
	// Si es ~0, el rayo es paralelo al plano
	if (fabs(denom) < 1e-6)
		return (-1.0f);
	
	// Vector desde el origen del rayo al punto del plano
	p_to_o = vec_sub(plane.point, ray.origin);
	
	// Calcular t
	t = vec3_dot(p_to_o, plane.normal) / denom;
	
	// Solo intersecciones positivas (delante del rayo)
	if (t < 0)
		return (-1.0f);
	
	return (t);
}

/**
 * Versión completa que llena la estructura hit_info
 */
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
	
	// Asegurar que la normal apunta hacia el rayo
	// (importante para iluminación correcta)
	if (vec3_dot(hit->normal, ray.direction) > 0)
	{
		hit->normal.x = -hit->normal.x;
		hit->normal.y = -hit->normal.y;
		hit->normal.z = -hit->normal.z;
	}
	
	return (1);
}
