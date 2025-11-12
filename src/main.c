/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfleritt <rfleritt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 08:36:03 by rfleritt          #+#    #+#             */
/*   Updated: 2025/11/12 09:30:51 by rfleritt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        write(2, "Usage: ./mini_rt <scene_file>\n", 30);
        return (1);
    }
    (void)argv;
    return (0);
}