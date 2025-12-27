/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfleritt <rfleritt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:21:36 by rfleritt          #+#    #+#             */
/*   Updated: 2025/12/14 11:06:14 by rfleritt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vec3 vec_new(float x, float y, float z)
{
    t_vec3 vec;
    
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return (vec);
}