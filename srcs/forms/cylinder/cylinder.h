#ifndef CYLINDER_H
# define CYLINDER_H

#include <raytracer.h>
#include <ray.h>

typedef struct	s_scene t_scene;

int				hit_cylinder(const t_ray ray, const t_cylinder cylinder, float *t);
int				find_closest_cylinder(t_scene scene, const t_ray ray, int *closest, float *t);

#endif
