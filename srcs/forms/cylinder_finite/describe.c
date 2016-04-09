#include <raytracer.h>

void	describe_cylinders_finite(t_scene scene)
{
	unsigned int	i;

	write(1, CYLINDERS_FINITE_INTRO, sizeof(CYLINDERS_FINITE_INTRO) - 1);
	i = 0;
	while (i < scene.cylinders_finite_nb)
	{
		printf("\t(%f, %f, %f) (%f, %f, %f) %f %i\n",
				scene.cylinders_finite[i].p.x, scene.cylinders_finite[i].p.y, scene.cylinders_finite[i].p.z,
				scene.cylinders_finite[i].q.x, scene.cylinders_finite[i].q.y, scene.cylinders_finite[i].q.z,
				scene.cylinders_finite[i].r, scene.cylinders_finite[i].m);
		++i;
	}
}