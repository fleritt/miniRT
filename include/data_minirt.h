/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_minirt.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:12:59 by rfleritt          #+#    #+#             */
/*   Updated: 2026/02/07 18:34:28 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_MINIRT_H
# define DATA_MINIRT_H

typedef enum s_order
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    A,
    D
}   t_order;

typedef enum s_type_scene
{
    SPHERE,
    PLANE,
    AMBIENT,
    CAMERA,
    LIGHT,
    CYLINDER,
    VOID
}   t_type_scene;

typedef struct s_vec3
{
    float x;
    float y;
    float z;
}   t_vec3;

typedef struct s_camera
{
    t_vec3  position;
    t_vec3  direction;
    t_vec3 forward;
    t_vec3 up;
    t_vec3 right;
    float   pov;
}   t_camera;

typedef struct s_color
{
    float r;
    float g;
    float b;
}   t_color;

typedef struct s_plane
{
    t_vec3 point;
    t_vec3 normal;
    t_color color;
}   t_plane;

typedef struct s_light
{
    t_vec3 position;
    float intensity;
    t_color color;
}   t_light;

typedef struct s_ambient
{
    float intensity;
    t_color color;
}   t_ambient;

typedef struct s_ray
{
    t_vec3 origin;
    t_vec3 direction;
}   t_ray;

typedef struct s_hit_info
{
    float t;
    t_vec3 point;
    t_vec3 normal;
    t_color color;
}   t_hit_info;

typedef struct s_sphere
{
    t_vec3 center;
    float radius;
    t_color color;
}   t_sphere;

typedef struct s_window
{
    mlx_t *mlx;
    mlx_image_t *mlx_image;
	int width;
    int height;
}	t_window;

typedef struct s_scene
{
    t_type_scene type;
    char **data;
    struct s_scene *next;
}   t_scene;

typedef struct s_scene_data
{
    t_camera camera;
    t_sphere *sphere;
    t_ambient ambient;
    t_plane *plane;
    t_light *light;
    int n_sphere;
    int n_plane;
    int n_light;
}   t_scene_data;

typedef struct s_data
{
    t_window *window;
    t_scene_data *scene;
    t_ray ray;
    t_scene *token;
}   t_data;

#endif