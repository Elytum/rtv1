#ifndef CYLINDER_finite_FINITE_H
# define CYLINDER_finite_FINITE_H

#include <raytracer.h>
#include <ray.h>

typedef struct	s_data t_data;

int				hit_cylinder_finite(const t_ray ray, const t_cylinder_finite cylinder_finite, double *t);
void			find_closest_cylinder_finite(t_data *data, const t_ray ray, double *t);
int				hit_any_cylinder_finite(t_data *data, const t_ray ray, double t);
int				cylinder_finite_normal(t_data *data);

#endif
