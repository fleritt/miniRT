/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:00:00 by ricardo           #+#    #+#             */
/*   Updated: 2026/02/07 18:21:55 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * Libera la lista de tokens parseados
 */
void	free_tokens(t_scene *token)
{
	t_scene	*temp;
	int		i;

	while (token)
	{
		temp = token->next;
		if (token->data)
		{
			i = 0;
			while (token->data[i])
			{
				free(token->data[i]);
				i++;
			}
			free(token->data);
		}
		free(token);
		token = temp;
	}
}

/**
 * Libera la escena completa
 */
void	free_scene(t_scene_data *scene)
{
	if (!scene)
		return ;
	if (scene->sphere)
		free(scene->sphere);
	if (scene->plane)
		free(scene->plane);
	if (scene->light)
		free(scene->light);
	free(scene);
}

/**
 * Limpieza completa de memoria
 */
void	cleanup_data(t_data *data)
{
	if (!data)
		return ;
	if (data->token)
		free_tokens(data->token);
	if (data->scene)
		free_scene(data->scene);
	if (data->window)
	{
		if (data->window->mlx_image)
			mlx_delete_image(data->window->mlx, data->window->mlx_image);
		if (data->window->mlx)
			mlx_terminate(data->window->mlx);
		free(data->window);
	}
	free(data);
}
