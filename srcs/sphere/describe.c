#include <raytracer.h>

void	describe_spheres(t_scene scene)
{
	int	i;

	write(1, SPHERES_INTRO, sizeof(SPHERES_INTRO) - 1);
	i = 0;
	while (i < scene.spheres_nb)
	{
		printf("\t(%f, %f, %f) %f\n",
			scene.spheres[i].x, scene.spheres[i].y, scene.spheres[i].z, scene.spheres[i].r);
		++i;
	}
}