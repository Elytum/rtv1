#ifndef CYLINDER_H
# define CYLINDER_H

#include <raytracer.h>
#include <ray.h>

typedef struct	s_data t_data;

int				hit_cylinder(const t_ray ray, const t_cylinder cylinder, double *t);
void			find_closest_cylinder(t_data *data, const t_ray ray, double *t);
int				hit_any_cylinder(t_data *data, const t_ray ray, double t);

#endif
