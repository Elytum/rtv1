#include <raytracer.h>

void	describe_cylinders(t_scene scene)
{
	int	i;

	write(1, CYLINDERS_INTRO, sizeof(CYLINDERS_INTRO) - 1);
	i = 0;
	while (i < scene.cylinders_nb)
	{
		printf("\t(%f, %f, %f) (%f, %f, %f) %f\n",
				scene.cylinders[i].x1, scene.cylinders[i].y1, scene.cylinders[i].z1,
				scene.cylinders[i].x2, scene.cylinders[i].y2, scene.cylinders[i].z2,
				scene.cylinders[i].r);
		++i;
	}
}