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

static int	check_planes(t_data *data, t_ray ray, t_hit_info *hit,
	float *closest_t)
{
	t_hit_info	temp_hit;
	int			i;
	int			found;

	found = (*closest_t >= 0);
	i = 0;
	while (i < data->scene->n_plane)
	{
		if (hit_plane_info(ray, data->scene->plane[i], &temp_hit))
		{
			if (*closest_t < 0 || temp_hit.t < *closest_t)
			{
				*closest_t = temp_hit.t;
				*hit = temp_hit;
				found = 1;
			}
		}
		i++;
	}
	return (found);
}

static int	check_cylinders(t_data *data, t_ray ray, t_hit_info *hit,
	float *closest_t)
{
	t_hit_info	temp_hit;
	int			i;
	int			found;

	found = (*closest_t >= 0);
	i = 0;
	while (i < data->scene->n_cylinder)
	{
		if (hit_cylinder_info(ray, data->scene->cylinder[i], &temp_hit))
		{
			if (*closest_t < 0 || temp_hit.t < *closest_t)
			{
				*closest_t = temp_hit.t;
				*hit = temp_hit;
				found = 1;
			}
		}
		i++;
	}
	return (found);
}

static int	find_closest_hit(t_data *data, t_ray ray, t_hit_info *hit)
{
	float	closest_t;
	int		found;

	closest_t = -1;
	found = check_spheres(data, ray, hit, &closest_t);
	if (closest_t < 0.01f && found)
		return (1);
	if (check_planes(data, ray, hit, &closest_t))
		found = 1;
	if (check_cylinders(data, ray, hit, &closest_t))
		found = 1;
	return (found);
}

void	ft_render(t_data *data)
{
	int			c[2];
	t_color		pixel;
	t_color		background;
	t_hit_info	hit;
	t_vec3		view_dir;

	c[0] = 0;
	background = (t_color){255, 255, 255};
	while (c[0] < HEIGHT)
	{
		c[1] = 0;
		while (c[1] < WIDTH)
		{
			init_hit_sphere(c[1], c[0], data);
			pixel = background;
			if (find_closest_hit(data, data->ray, &hit))
			{
				view_dir = vec_norm(vec_sub(data->ray.origin, hit.point));
				pixel = calculate_lighting(data, hit, view_dir);
			}
			ft_render_image(pixel, c[1], c[0], data->window);
			c[1]++;
		}
		c[0]++;
	}
}
