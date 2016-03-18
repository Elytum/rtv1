#ifndef PLANE_H
# define PLANE_H

#include <raytracer.h>
#include <ray.h>

typedef struct	s_scene t_scene;

int				hit_plane(const t_ray ray, const t_plane sphere, float *t);
void			find_closest_plane(t_scene scene, const t_ray ray, int *closest, float *t);

#endif
