#ifndef SPHERE_H
# define SPHERE_H

#include <raytracer.h>
#include <ray.h>

typedef struct	s_scene t_scene;

int				hit_sphere(const t_ray ray, const t_sphere sphere, float *t);
void			find_closest_sphere(t_scene scene, const t_ray ray, int *closest, float *t);

#endif
