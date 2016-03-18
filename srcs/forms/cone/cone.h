#ifndef CONE_H
# define CONE_H

#include <raytracer.h>
#include <ray.h>

typedef struct	s_scene t_scene;

int				hit_cone(const t_ray ray, const t_cone cone, float *t);
int				find_closest_cone(t_scene scene, const t_ray ray, int *closest, float *t);

#endif
