/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 16:50:07 by rfleritt          #+#    #+#             */
/*   Updated: 2026/01/29 19:06:43 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
int hit_sphere(t_ray ray, t_sphere sphere)
{
    t_vec3 oc;
    float a;
    float b;
    float c;
    float dis;
    float t;

    oc = vec_sub(ray.origin, sphere.center);
    a = vec3_dot(ray.direction, ray.direction);
    b = 2.0f * vec3_dot(oc, ray.direction);
    c = vec3_dot(oc, oc) - sphere.radius * sphere.radius;
    dis = b * b - 4 * a * c;
    if (dis < 0)
        return (-1.0f);
    t = (-b - sqrt(dis)) / (2.0f * a);
    if (t > 0)
        return (t);
    return (-1.0f);
}

void init_hit_sphere(int x, int y, t_data *data)
{
    float scale;
    float aspect_ratio;
    float px;
    float py;

    aspect_ratio = (float)WIDTH / (float)HEIGHT;
    scale = tan((data->scene->camera.pov * M_PI / 180.0f) / 2.0f);
    px = (2.0f * ((x + 0.5f) / WIDTH) - 1.0f) * aspect_ratio * scale;
    py = 1.0f - 2.0f * ((y + 0.5f) / HEIGHT) * scale;
    data->ray.origin = data->scene->camera.position;
    data->ray.direction = vec_norm(vec_add(data->scene->camera.forward, vec_add(vec_mult(data->scene->camera.right, px), vec_mult(data->scene->camera.up, py))));
} 