/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:04:25 by rfleritt          #+#    #+#             */
/*   Updated: 2026/02/07 18:21:57 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int main(int argc, char **argv)
{
    t_data *data;

    if (argc != 2)
        return (ft_msg_error("One scene requires", 1));
    data = init_scene(argv[1]);
    if (!data || !data->token)
        return (1);
    init_window(data);
    cleanup_data(data);
    return (0);
}
