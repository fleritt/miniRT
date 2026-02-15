/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:44:11 by rfleritt          #+#    #+#             */
/*   Updated: 2026/02/07 18:30:36 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

double lerp(float a, float b, float t)
{
    return (a + t * (b - a));
}

t_color lerp_color(t_color c1, t_color c2, float t)
{
    t_color res;

    res.r = lerp(c1.r, c2.r, t);
    res.g = lerp(c1.g, c2.g, t);
    res.b = lerp(c1.b, c2.b, t);
    return (res);
}

void ft_render_image(t_color color, int x, int y, t_window *window)
{
    uint8_t *pixels;
    int index;

    index = (y * WIDTH + x) * 4;
    pixels = window->mlx_image->pixels;

    pixels[index] = (uint8_t)color.r;
    pixels[index + 1] = (uint8_t)color.g;
    pixels[index + 2] = (uint8_t)color.b;
    pixels[index + 3] = (uint8_t)255;
}

/**
 * Encuentra el objeto más cercano intersectado por el rayo
 * Retorna 1 si hay intersección, 0 si no
 * OPTIMIZADO: early exit cuando encuentra hit muy cercano
 */
static int	find_closest_hit(t_data *data, t_ray ray, t_hit_info *hit)
{
	t_hit_info	temp_hit;
	float		closest_t;
	int			i;
	int			found;

	closest_t = -1;
	found = 0;

	// Comprobar esferas con early exit
	i = 0;
	while (i < data->scene->n_sphere)
	{
		if (hit_sphere_info(ray, data->scene->sphere[i], &temp_hit))
		{
			if (closest_t < 0 || temp_hit.t < closest_t)
			{
				closest_t = temp_hit.t;
				*hit = temp_hit;
				found = 1;

				// Early exit: si el hit está muy cerca, no necesitamos buscar más
				if (closest_t < 0.01f)
					return (1);
			}
		}
		i++;
	}

	// Comprobar planos
	i = 0;
	while (i < data->scene->n_plane)
	{
		if (hit_plane_info(ray, data->scene->plane[i], &temp_hit))
		{
			if (closest_t < 0 || temp_hit.t < closest_t)
			{
				closest_t = temp_hit.t;
				*hit = temp_hit;
				found = 1;
			}
		}
		i++;
	}
    // Comprobar cilindros
    i = 0;
    while (i < data->scene->n_cylinder)
    {
        if (hit_cylinder_info(ray, data->scene->cylinder[i], &temp_hit))
        {
            if (closest_t < 0 || temp_hit.t < closest_t)
            {
                closest_t = temp_hit.t;
                *hit = temp_hit;
                found = 1;
            }
        }
        i++;
    }

	return (found);
}

void ft_render(t_data *data)
{
    int c[2];
    t_color pixel;
    t_color background;
    t_hit_info hit;
    t_vec3 view_dir;

    c[0] = 0;
    background = (t_color){255,255,255};
    while(c[0] < HEIGHT)
    {
        c[1] = 0;
        while(c[1] < WIDTH)
        {
            init_hit_sphere(c[1], c[0], data);
            pixel = background;

            // Buscar intersección más cercana
            if (find_closest_hit(data, data->ray, &hit))
            {
                // Vector desde el punto hacia la cámara
                view_dir = vec_norm(vec_sub(data->ray.origin, hit.point));

                // Calcular iluminación completa
                pixel = calculate_lighting(data, hit, view_dir);
            }

            ft_render_image(pixel, c[1], c[0], data->window);
            c[1]++;
        }
        c[0]++;
    }
}
