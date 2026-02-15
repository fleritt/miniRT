#include "../../include/minirt.h"

int hit_cylinder_info(t_ray ray, t_cylinder cy, t_hit_info *hit)
{
    t_vec3 oc;
    float a;
    float b;
    float c;
    float discriminant;
    float sqrt_d;
    float t;
    float height_proj;
    t_vec3 point;
    t_vec3 normal;

    oc = vec_sub(ray.origin, cy.center);

    a = vec3_dot(ray.direction, ray.direction)
        - pow(vec3_dot(ray.direction, cy.axis), 2);

    b = 2 * (vec3_dot(ray.direction, oc)
        - vec3_dot(ray.direction, cy.axis)
        * vec3_dot(oc, cy.axis));

    c = vec3_dot(oc, oc)
        - pow(vec3_dot(oc, cy.axis), 2)
        - cy.radius * cy.radius;

    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return (0);

    sqrt_d = sqrt(discriminant);
    t = (-b - sqrt_d) / (2 * a);
    if (t < 0.001f)
        t = (-b + sqrt_d) / (2 * a);
    if (t < 0.001f)
        return (0);

    point = vec_add(ray.origin, vec_mult(ray.direction, t));
    height_proj = vec3_dot(vec_sub(point, cy.center), cy.axis);

    if (height_proj < 0 || height_proj > cy.height)
        return (0);

    normal = vec_sub(
        vec_sub(point, cy.center),
        vec_mult(cy.axis, height_proj)
    );
    normal = vec_norm(normal);

    hit->t = t;
    hit->point = point;
    hit->normal = normal;
    hit->color = cy.color;

    if (vec3_dot(hit->normal, ray.direction) > 0)
        hit->normal = vec_mult(hit->normal, -1);

    return (1);
}
