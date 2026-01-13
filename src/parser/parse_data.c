/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfleritt <rfleritt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 14:46:18 by rfleritt          #+#    #+#             */
/*   Updated: 2026/01/13 14:00:46 by rfleritt         ###   ########.fr       */
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
    t_scene *temp;
    int n_light;

    temp = data->token;
    n_light = found_count_element(temp, LIGHT);
    if (n_light == 0)
        return ;
    data->scene->light = malloc(sizeof(t_light) * n_light);
    n_light = 0;
    while(temp)
    {
        if (temp->type == LIGHT)
        {
            data->scene->light[n_light] = set_light(temp->data);
            n_light++;
        }
        temp = temp->next;
    }
}

void parse_plane(t_data *data)
{
    t_scene *temp;
    int n_plane;

    temp = data->token;
    n_plane = found_count_element(temp, PLANE);
    if (n_plane == 0)
        return ;
    data->scene->plane = malloc(sizeof(t_plane) * n_plane);
    n_plane = 0;
    while(temp)
    {
        if (temp->type = PLANE)
        {
            data->scene->plane[n_plane] = set_plane(temp->data);
            n_plane++;
        }
        temp = temp->next;
    }
}

void parse_camera(t_data *data)
{
    t_scene *temp;
    int n_camera;

    temp = data->token;
    n_camera = found_count_element(temp, CAMERA);
    if (n_camera == 0)
        exit_msg_error("Program needs one camera");
    else if (n_camera > 1)
        exit_msg_error("Program needs only one camera");
    while(temp)
    {
        if (temp->type == CAMERA)
            data->scene->camera = set_camera(temp->data);
        temp = temp->next;
    }
}

void parse_ambient(t_data *data)
{
    t_scene *temp;
    int n_ambient;

    temp = data->token;
    n_ambient = found_count_element(temp, AMBIENT);
    if (n_ambient == 0)
        exit_msg_error("Program needs one light ambient");
    else if (n_ambient > 1)
        exit_msg_error("Program needs only light ambient");
    while(temp)
    {
        if (temp->type == AMBIENT)
            data->scene->ambient = set_ambient(temp->data);
        temp = temp->next;
    }
}