#include <raytracer.h>

void	describe_cones(t_scene scene)
{
	int	i;

	write(1, CONES_INTRO, sizeof(PLANES_INTRO) - 1);
	i = 0;
	while (i < scene.cones_nb)
	{
		printf("\t(%f, %f, %f) %f (%f, %f, %f) %f %i\n",
				scene.cones[i].x1, scene.cones[i].y1, scene.cones[i].z1,
				scene.cones[i].r1, scene.cones[i].x2, scene.cones[i].y2,
				scene.cones[i].z2, scene.cones[i].r2, scene.cones[i].m);
		++i;
	}
}
