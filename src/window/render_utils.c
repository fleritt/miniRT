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

double	lerp(float a, float b, float t)
{
	return (a + t * (b - a));
}

t_color	lerp_color(t_color c1, t_color c2, float t)
{
	t_color	res;

	res.r = lerp(c1.r, c2.r, t);
	res.g = lerp(c1.g, c2.g, t);
	res.b = lerp(c1.b, c2.b, t);
	return (res);
}

void	ft_render_image(t_color color, int x, int y, t_window *window)
{
	uint8_t	*pixels;
	int		index;

	index = (y * WIDTH + x) * 4;
	pixels = window->mlx_image->pixels;
	pixels[index] = (uint8_t)color.r;
	pixels[index + 1] = (uint8_t)color.g;
	pixels[index + 2] = (uint8_t)color.b;
	pixels[index + 3] = (uint8_t)255;
}

int	check_spheres(t_data *data, t_ray ray, t_hit_info *hit,
	float *closest_t)
{
	t_hit_info	temp_hit;
	int			i;
	int			found;

	found = 0;
	i = 0;
	while (i < data->scene->n_sphere)
	{
		if (hit_sphere_info(ray, data->scene->sphere[i], &temp_hit))
		{
			if (*closest_t < 0 || temp_hit.t < *closest_t)
			{
				*closest_t = temp_hit.t;
				*hit = temp_hit;
				found = 1;
				if (*closest_t < 0.01f)
					return (1);
			}
		}
		i++;
	}
	return (found);
}
