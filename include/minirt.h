/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 08:36:35 by rfleritt          #+#    #+#             */
/*   Updated: 2026/02/07 18:32:37 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../libs/libft/libft.h"
# include "../libs/mlx/include/MLX42/MLX42.h"
# include "data_minirt.h"

# define WIDTH 800
# define HEIGHT 600
# define M_PI 3.14159265358979323846

void init_window(t_data *data);
void key_close_window(mlx_key_data_t keydata, void *param);
void ft_render(t_data *data);
void exit_msg_error(char *err);
int hit_sphere_info(t_ray ray, t_sphere sphere, t_hit_info *hit);
float hit_plane(t_ray ray, t_plane plane);
int hit_plane_info(t_ray ray, t_plane plane, t_hit_info *hit);
int ft_msg_error(char *err, int ret);
t_data *init_scene(char *scene);
float vec3_dot(t_vec3 a, t_vec3 b);
float vec_length(t_vec3 v);
t_vec3 vec_new(float x, float y, float z);
t_vec3 vec_mult(t_vec3 v, float t);
t_vec3 vec_sub(t_vec3 a, t_vec3 b);
t_vec3 vec_add(t_vec3 a, t_vec3 b);
t_vec3 vec_norm(t_vec3 v);
t_vec3 vec_cross(t_vec3 a, t_vec3 b);
t_vec3 parse_vec(char *vec);
void init_hit_sphere(int x, int y, t_data *data);
void init_camera(t_data *data);
void key_register(mlx_key_data_t keydata, void *param);
float hit_sphere(t_ray ray, t_sphere sphere);
void parse_scene(t_data *data);
void parse_sphere(t_data *data);
void parse_ambient(t_data *data);
void parse_light(t_data *data);
void parse_plane(t_data *data);
void parse_camera(t_data *data);
t_sphere set_sphere(char **data);
t_light set_light(char **data);
t_plane set_plane(char **data);
t_camera set_camera(char **data);
t_ambient set_ambient(char **data);
t_color parse_color(char *color);
t_color calculate_ambient(t_ambient ambient, t_color object_color);
t_color calculate_diffuse(t_light light, t_hit_info hit);
t_color add_colors(t_color c1, t_color c2);
int is_in_shadow(t_data *data, t_hit_info hit, t_light light);
t_color calculate_specular(t_light light, t_hit_info hit, t_vec3 view_dir);
t_color calculate_lighting(t_data *data, t_hit_info hit, t_vec3 view_dir);
void free_tokens(t_scene *token);
void free_scene(t_scene_data *scene);
void cleanup_data(t_data *data);

#endif