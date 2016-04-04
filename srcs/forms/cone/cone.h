#ifndef CONE_H
# define CONE_H

#include <raytracer.h>
#include <ray.h>

typedef struct	s_data t_data;

int				hit_cone(const t_ray ray, const t_cone cone, double *t);
void			find_closest_cone(t_data *data, const t_ray ray, double *t);
int				hit_any_cone(t_data *data, const t_ray ray, double t);

#endif
