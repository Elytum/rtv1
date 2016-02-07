#include <raytracer.h>

void	describe_lights(t_scene scene)
{
	int	i;

	write(1, LIGHTS_INTRO, sizeof(LIGHTS_INTRO) - 1);
	i = 0;
	while (i < scene.lights_nb)
	{
		write(1, "\t", 1);
		vec3_describe(scene.lights[i].pos);
		dprintf(1, "(%f, %f, %f)\n",
				scene.lights[i].r, scene.lights[i].g, scene.lights[i].b);
		++i;
	}
}