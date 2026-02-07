/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:30:00 by ricardo           #+#    #+#             */
/*   Updated: 2026/02/07 18:34:27 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * Verifica si un punto está en sombra respecto a una luz
 * Lanza un rayo desde el punto hacia la luz
 * Si intersecta algo antes de llegar a la luz, está en sombra
 * OPTIMIZADO: usa hit_sphere en vez de hit_sphere_info (más rápido)
 * OPTIMIZADO: early exit en cuanto encuentra un objeto bloqueando
 */
int	is_in_shadow(t_data *data, t_hit_info hit, t_light light)
{
	t_ray	shadow_ray;
	t_vec3	light_dir;
	float	light_distance;
	float	t;
	int		i;

	// Vector y distancia hacia la luz
	light_dir = vec_sub(light.position, hit.point);
	light_distance = vec_length(light_dir);
	light_dir = vec_norm(light_dir);
	
	// Rayo desde el punto (con pequeño offset) hacia la luz
	shadow_ray.origin = vec_add(hit.point, vec_mult(hit.normal, 0.001f));
	shadow_ray.direction = light_dir;
	
	// Comprobar esferas (early exit en cuanto encuentra oclusión)
	i = 0;
	while (i < data->scene->n_sphere)
	{
		t = hit_sphere(shadow_ray, data->scene->sphere[i]);
		if (t > 0.001f && t < light_distance)
			return (1);
		i++;
	}
	
	// Comprobar planos (early exit)
	i = 0;
	while (i < data->scene->n_plane)
	{
		t = hit_plane(shadow_ray, data->scene->plane[i]);
		if (t > 0.001f && t < light_distance)
			return (1);
		i++;
	}
	
	return (0);
}

/**
 * Calcula la componente especular (brillo/reflejo)
 * Usa el modelo de Phong: specular = light × pow(dot(reflect, view), shininess)
 */
t_color	calculate_specular(t_light light, t_hit_info hit, t_vec3 view_dir)
{
	t_vec3	light_dir;
	t_vec3	reflect_dir;
	float	spec;
	t_color	result;
	float	shininess;

	shininess = 32.0f; // Brillo del material (más alto = más brillante)
	
	// Vector hacia la luz
	light_dir = vec_norm(vec_sub(light.position, hit.point));
	
	// Vector reflejado: R = 2 * (N·L) * N - L
	reflect_dir = vec_sub(vec_mult(hit.normal, 2.0f * vec3_dot(hit.normal, light_dir)), light_dir);
	reflect_dir = vec_norm(reflect_dir);
	
	// Calcular componente especular
	spec = vec3_dot(reflect_dir, view_dir);
	if (spec < 0)
		spec = 0;
	
	// Elevar a la potencia (shininess)
	spec = pow(spec, shininess);
	
	// Color especular (blanco puro modulado por la luz)
	result.r = (light.color.r / 255.0f) * light.intensity * spec * 255.0f;
	result.g = (light.color.g / 255.0f) * light.intensity * spec * 255.0f;
	result.b = (light.color.b / 255.0f) * light.intensity * spec * 255.0f;
	
	return (result);
}

/**
 * Calcula la iluminación completa para un punto:
 * - Luz ambiental (siempre)
 * - Luz difusa (si no está en sombra)
 * - Luz especular (si no está en sombra)
 * OPTIMIZADO: usa FAST_RENDER para skip sombras en escenas pesadas
 */
t_color	calculate_lighting(t_data *data, t_hit_info hit, t_vec3 view_dir)
{
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;
	t_color	final_color;
	int		in_shadow;

	// Luz ambiental (siempre presente)
	ambient = calculate_ambient(data->scene->ambient, hit.color);
	
	// Inicializar difusa y especular
	diffuse = (t_color){0, 0, 0};
	specular = (t_color){0, 0, 0};
	
	// Si hay luz, calcular difusa y especular
	if (data->scene->light && data->scene->n_light > 0)
	{
		#ifdef FAST_RENDER
			// Modo rápido: sin sombras
			in_shadow = 0;
		#else
			// Modo normal: con sombras
			in_shadow = is_in_shadow(data, hit, data->scene->light[0]);
		#endif
		
		if (!in_shadow)
		{
			diffuse = calculate_diffuse(data->scene->light[0], hit);
			specular = calculate_specular(data->scene->light[0], hit, view_dir);
		}
	}
	
	// Sumar todas las componentes
	final_color = add_colors(ambient, diffuse);
	final_color = add_colors(final_color, specular);
	
	return (final_color);
}
