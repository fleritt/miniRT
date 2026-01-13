/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elemens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfleritt <rfleritt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 10:55:25 by rfleritt          #+#    #+#             */
/*   Updated: 2026/01/04 11:12:45 by rfleritt         ###   ########.fr       */
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
    printf("%s", split[2]);
    vec3.x = atof(split[0]);
    vec3.y = atof(split[1]);
    vec3.z = atof(split[2]);
    i = -1;
    while (split[++i])
        free(split[i]);
    return (free(split), vec3);
}