/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfleritt <rfleritt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 14:46:18 by rfleritt          #+#    #+#             */
/*   Updated: 2025/12/27 15:33:07 by rfleritt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int found_count_element(t_scene *scene, t_type_scene type)
{
    int n_element;

    n_element = 0;
    while(scene)
    {
        if (scene->type == type)
            n_element++;
        scene = scene->next;
    }
    return (n_element);
}

void parse_sphere(t_data *data)
{
    t_scene *temp;
    int n_sphere;

    temp = data->token;
    n_sphere = found_count_element(temp, SPHERE);
    if (n_sphere == 0)
        return ;
    data->scene->sphere = malloc(sizeof(t_sphere) * n_sphere);
    n_sphere = 0;
    while(temp)
    {
        if (temp->type == SPHERE)
        {
            data->scene->sphere[n_sphere] = set_sphere(temp->data);
            n_sphere++;
        }
        temp = temp->next;
    }
}

void parse_light(t_data *data)
{
    
}

void parse_plane(t_data *data)
{
    
}

void parse_camera(t_data *data)
{
    
}

void parse_ambient(t_data *data)
{
    
}