#include "../../include/minirt.h"

void parse_cylinder(t_data *data)
{
    t_scene *temp;
    int n_cylinder;

    temp = data->token;
    n_cylinder = found_count_element(temp, CYLINDER);
    if (n_cylinder == 0)
        return ;

    data->scene->cylinder = malloc(sizeof(t_cylinder) * n_cylinder);
    n_cylinder = 0;

    while (temp)
    {
        if (temp->type == CYLINDER)
        {
            data->scene->cylinder[n_cylinder] = set_cylinder(temp->data);
            n_cylinder++;
        }
        temp = temp->next;
    }
    data->scene->n_cylinder = n_cylinder;
}
