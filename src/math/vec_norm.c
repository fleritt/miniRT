/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_norm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfleritt <rfleritt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:23:11 by rfleritt          #+#    #+#             */
/*   Updated: 2025/12/14 12:00:30 by rfleritt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vec3 vec_norm(t_vec3 v)
{
    float len;

    len = vec_length(v);
    if (len == 0.0f)
		return (vec_new(0, 0, 0));
    return (vec_mult(v, 1.0 / len));
}