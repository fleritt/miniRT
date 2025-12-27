/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfleritt <rfleritt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:13:48 by rfleritt          #+#    #+#             */
/*   Updated: 2025/12/27 14:20:32 by rfleritt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int set_type(char *line, t_scene *token)
{
    if(ft_strnstr(line, "#", 1))
        return(free(line), 0);
    else if(ft_strnstr(line, "sp", 3))
        return(free(line), token->type = SPHERE, 0);
    else if(ft_strnstr(line, "pl", 3))
        return(free(line), token->type = PLANE, 0);
    else if(ft_strnstr(line, "A", 3))
        return(free(line), token->type = AMBIENT, 0);
    else if(ft_strnstr(line, "C", 3))
        return(free(line), token->type = CAMERA, 0);
    else if(ft_strnstr(line, "L", 3))
        return(free(line), token->type = LIGHT, 0);
    else if(ft_strnstr(line, "cy", 3))
        return(free(line), token->type = CYLINDER, 0);
    else if(ft_strnstr(line, "", 2))
        return(free(line), 0);
    else 
        return (free(line), 1);
}

void token_add_back(t_scene **back, t_scene **add)
{
    t_scene *temp;

    temp = *back;
    while (temp)
    {
        if(temp->next == NULL)
        {
            temp->next = *add;
            return ;
        }
        temp = temp->next;
    }
}

int set_token(char *line, t_scene **token)
{
    t_scene *add;

    add = malloc(sizeof(t_scene));
    add->type = VOID;
    add->next = NULL;
    if (set_type(ft_strtrim(line, " "), add))
        return (ft_msg_error("Invalid scene", 1));
    if (add->type == VOID)
        return (free(add), 0);
    add->data = ft_split(line, ' ');
    if (*token == NULL)
        *token = add;
    else
        token_add_back(token, &add);
    return (0);
}

int tokenize_scene(char *scene, t_data *data)
{
    int i;
    int fd;
    char *line;

    i = ft_strlen(scene);
    if (scene[i - 1] != 't'|| scene[i - 2] != 'r' || scene[i - 3] != '.')
        return (ft_msg_error("The file is only .rt format", 1));
    if (access(scene, F_OK) || access(scene, R_OK))
        return (ft_msg_error("No existe el archivo pelotudo", 1));
    fd = open(scene, O_RDONLY);
    data->token = NULL;
    line = get_next_line(fd);
    if (line == NULL)
        return (1);
    while(line)
    {
        if (set_token(line, &data->token))
        {
            free(data);
            free(line);
            return(1);
        }
        free(line);
        line = get_next_line(fd);
    }
    return (0);
}

t_data *init_scene(char *scene)
{
    t_data *data;
    
    data = malloc(sizeof(t_data));
    if (tokenize_scene(scene, data))
        return(NULL);
    if (parse_scene(data))
        return (NULL);
    return (data);
}