/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfleritt <rfleritt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 16:26:16 by rfleritt          #+#    #+#             */
/*   Updated: 2026/03/12 17:13:57 by rfleritt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	parse_ambient(t_data *data)
{
	t_scene	*temp;
	int		n_ambient;

	temp = data->token;
	n_ambient = found_count_element(temp, AMBIENT);
	if (n_ambient == 0)
		exit_msg_error("Program needs one light ambient");
	else if (n_ambient > 1)
		exit_msg_error("Program needs only light ambient");
	while (temp)
	{
		if (temp->type == AMBIENT)
			data->scene->ambient = set_ambient(temp->data);
		temp = temp->next;
	}
}

t_sphere	set_sphere(char **data)
{
	t_sphere	sphere;

	sphere.center = parse_vec(data[1]);
	sphere.radius = ft_atof(data[2]);
	sphere.color = parse_color(data[3]);
	return (sphere);
}
