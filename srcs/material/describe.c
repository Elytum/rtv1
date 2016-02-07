#include <raytracer.h>

void	describe_materials(t_scene scene)
{
	int	i;

	write(1, MATERIALS_INTRO, sizeof(MATERIALS_INTRO) - 1);
	i = 0;
	while (i < scene.materials_nb)
	{
		printf("\t[%f, %f, %f] %f\n",
				scene.materials[i].r, scene.materials[i].g, scene.materials[i].b,
				scene.materials[i].c);
		++i;
	}
}