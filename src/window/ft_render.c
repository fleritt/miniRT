/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfleritt <rfleritt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:44:11 by rfleritt          #+#    #+#             */
/*   Updated: 2026/01/13 14:07:28 by rfleritt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

double lerp(float a, float b, float t)
{
    return (a + t * (b - a));
}

t_color lerp_color(t_color c1, t_color c2, float t)
{
    t_color res;

    res.r = lerp(c1.r, c2.r, t);
    res.g = lerp(c1.g, c2.g, t);
    res.b = lerp(c1.b, c2.b, t);
    return (res);
}

void ft_render_image(t_color color, int x, int y, t_window *window)
{
    uint8_t *pixels;
    int index;

    index = (y * WIDTH + x) * 4;
    pixels = window->mlx_image->pixels;

    pixels[index] = (uint8_t)color.r;
    pixels[index + 1] = (uint8_t)color.g;
    pixels[index + 2] = (uint8_t)color.b;
    pixels[index + 3] = (uint8_t)255;
}

void ft_render(t_data *data)
{
    int c[2];
    float t;
    t_color pixel;
    
    c[0] = 0;
    t = (float)c[0] / (HEIGHT - 1);
    pixel = lerp_color(data->window->color[0], data->window->color[1], t);
    while(c[0] < HEIGHT)
    {
        c[1] = 0;
        while(c[1] < WIDTH)
        {
            init_hit_sphere(c[1], c[0], data);
            if ((hit_sphere(data->ray, data->scene->sphere)) >= 0)
                ft_render_image(data->scene->sphere.color, c[1], c[0], data->window);
            else
                ft_render_image(pixel, c[1], c[0], data->window);
            c[1]++;
        }
        t = (float)c[0] / (HEIGHT - 1);
        pixel = lerp_color(data->window->color[0], data->window->color[1], t);
        c[0]++;
    }
}