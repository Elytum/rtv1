#include <raytracer.h>

void	describe_planes(t_scene scene)
{
	unsigned int	i;

	write(1, PLANES_INTRO, sizeof(PLANES_INTRO) - 1);
	i = 0;
	while (i < scene.planes_nb)
	{
		printf("\t(%f, %f, %f)\n", scene.planes[i].x, scene.planes[i].y, scene.planes[i].z);
		++i;
	}
}