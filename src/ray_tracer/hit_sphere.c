/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 16:50:07 by rfleritt          #+#    #+#             */
/*   Updated: 2026/02/07 18:30:36 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * Intersección rayo-esfera OPTIMIZADA
 * Reduce operaciones usando b' = b/2
 */
float hit_sphere(t_ray ray, t_sphere sphere)
{
    t_vec3 oc;
    float a;
    float half_b;
    float c;
    float discriminant;
    float sqrt_d;
    float t;

    oc = vec_sub(ray.origin, sphere.center);
    a = vec3_dot(ray.direction, ray.direction);
    half_b = vec3_dot(oc, ray.direction);  // Uso b/2 en vez de b
    c = vec3_dot(oc, oc) - sphere.radius * sphere.radius;
    
    // discriminante = (b/2)² - ac
    discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
        return (-1.0f);
    
    sqrt_d = sqrtf(discriminant);
    
    // t = (-b/2 - sqrt(discriminante)) / a
    t = (-half_b - sqrt_d) / a;
    if (t > 0.001f)  // Evitar self-intersection
        return (t);
    
    // Intentar la otra raíz
    t = (-half_b + sqrt_d) / a;
    if (t > 0.001f)
        return (t);
    
    return (-1.0f);
}

int hit_sphere_info(t_ray ray, t_sphere sphere, t_hit_info *hit)
{
    float t;

    t = hit_sphere(ray, sphere);
    if (t < 0)
        return (0);
    hit->t = t;
    hit->point = vec_add(ray.origin, vec_mult(ray.direction, t));
    hit->normal = vec_norm(vec_sub(hit->point, sphere.center));
    hit->color = sphere.color;
    return (1);
}

void init_hit_sphere(int x, int y, t_data *data)
{
    float scale;
    float aspect_ratio;
    float px;
    float py;
    t_vec3 ray_dir;

    aspect_ratio = (float)WIDTH / (float)HEIGHT;
    scale = tan((data->scene->camera.pov * M_PI / 180.0f) / 2.0f);
    px = (2.0f * ((x + 0.5f) / WIDTH) - 1.0f) * aspect_ratio * scale;
    py = (1.0f - 2.0f * ((y + 0.5f) / HEIGHT)) * scale;
    
    // Construir dirección del rayo: forward + right*px + up*py
    ray_dir = data->scene->camera.forward;
    ray_dir = vec_add(ray_dir, vec_mult(data->scene->camera.right, px));
    ray_dir = vec_add(ray_dir, vec_mult(data->scene->camera.up, py));
    
    data->ray.origin = data->scene->camera.position;
    data->ray.direction = vec_norm(ray_dir);
} 