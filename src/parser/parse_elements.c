/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfleritt <rfleritt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 10:55:25 by rfleritt          #+#    #+#             */
/*   Updated: 2026/01/13 14:01:29 by rfleritt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vec3 parse_vec(char *vec)
{
    char **split;
    int i;
    int parse;
    t_vec3 vec3;

    i = 0;
    while (vec)
    {
        if(vec[i] == ',')
            parse++;
        i++;
    }
    if(parse != 2)
        exit_msg_error("invalid data vecs");
    split = ft_split(vec, ',');
    vec3.x = ft_atof(split[0]);
    vec3.y = ft_atof(split[1]);
    vec3.z = ft_atof(split[2]);
    i = -1;
    while (split[++i])
        free(split[i]);
    return (free(split), vec3);
}

t_color parse_color(char *color)
{
    char **split;
    int i;
    int parse;
    t_color rgb;

    i = -1;
    while (color)
    {
        if(color[++i] == ',')
            parse++;
    }
    if(parse != 2)
        exit_msg_error("invalid data vecs");
    split = ft_split(color, ',');
    rgb.r = ft_atof(split[0]);
    rgb.g = ft_atof(split[1]);
    rgb.b = ft_atof(split[2]);
    i = -1;
    while (split[++i])
        free(split[i]);
    if (rgb.r < 0.0f || rgb.r > 255.0f
        || rgb.g < 0.0f || rgb.g > 255.0f
        || rgb.b < 0.0f || rgb.b > 255.0f)
        return(free(split), exit_msg_error("Color admit numbers 0 to 255"), rgb);
    return (free(split), rgb);
}
