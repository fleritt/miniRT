/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfleritt <rfleritt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 08:36:35 by rfleritt          #+#    #+#             */
/*   Updated: 2025/12/27 14:21:18 by rfleritt         ###   ########.fr       */
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
void init_hit_sphere(int x, int y, t_data *data);
void init_camera(t_data *data);
void key_register(mlx_key_data_t keydata, void *param);
int hit_sphere(t_ray ray, t_sphere sphere);
int parse_scene(t_data *data);

#endif