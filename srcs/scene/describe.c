#include <raytracer.h>

void	descibe_scene(t_scene scene)
{
	printf("Camera: (%f, %f, %f)\nNumber of planes: %i\nNumber of spheres: %i\nNumber of cylinders: %i\nNumber of cones: %i\n\n",
		scene.camera_x, scene.camera_y, scene.camera_z, scene.planes_nb, scene.spheres_nb, scene.cylinders_nb, scene.cones_nb);
	if (scene.planes_nb)
		describe_planes(scene);
	if (scene.spheres_nb)
		describe_spheres(scene);
	if (scene.cylinders_nb)
		describe_cylinders(scene);
	if (scene.cones_nb)
		describe_cones(scene);
}