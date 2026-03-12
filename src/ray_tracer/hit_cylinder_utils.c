/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfleritt <rfleritt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 17:24:19 by rfleritt          #+#    #+#             */
/*   Updated: 2026/03/12 17:40:08 by rfleritt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	cylinder_body_hit(t_ray ray, t_cylinder cy, t_hit_info *hit)
{
	float	a;
	float	b;
	float	discriminant;
	float	sqrt_d;
	float	t;

	discriminant = cylinder_disc(ray, cy, &a, &b);
	if (discriminant < 0)
		return (0);
	sqrt_d = sqrt(discriminant);
	t = (-b - sqrt_d) / (2 * a);
	if (t < 0.001f)
		t = (-b + sqrt_d) / (2 * a);
	if (t <= 0.001f)
		return (0);
	return (fill_cyl(ray, cy, t, hit));
}

int	hit_cylinder_info(t_ray ray, t_cylinder cy, t_hit_info *hit)
{
	if (cylinder_body_hit(ray, cy, hit))
		return (1);
	return (hit_cylinder_caps(ray, cy, hit));
}
