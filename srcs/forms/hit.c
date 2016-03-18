#include <forms.h>

int				find_closest(t_scene scene, const t_ray ray, int *closest, float *t)
{
	find_closest_sphere(scene, ray, closest, t);
	find_closest_plane(scene, ray, closest, t);
	find_closest_cone(scene, ray, closest, t);
	find_closest_cylinder(scene, ray, closest, t);
	return (closest[1] != -1);
}