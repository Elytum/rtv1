#include <raytracer.h>
#include <tools.h>

static void		*extract_data(int fd, int size)
{
	const char	error[] = "Couldn't extract data\n";
	void		*ret;

	if (size == 0)
		return (NULL);
	ret = safe_malloc(size);
	if (read(fd, ret, size) != size)
	{
		write(2, error, sizeof(error) - 1);
		exit(1);
	}
	return (ret);
}

void			init_scene(int fd, t_scene *scene)
{
	t_header	header;
	// const char	error[] = "Extra data in map\n";

	if (!(read(fd, &header, sizeof(header)) == sizeof(header)))
		exit(0);
	scene->materials = extract_data(fd, sizeof(t_material) * header.materials_nb);
	scene->lights = extract_data(fd, sizeof(t_light) * header.lights_nb);
	scene->planes = extract_data(fd, sizeof(t_plane) * header.planes_nb);
	scene->spheres = extract_data(fd, sizeof(t_sphere) * header.spheres_nb);
	scene->cylinders = extract_data(fd, sizeof(t_cylinder) * header.cylinders_nb);
	scene->cones = extract_data(fd, sizeof(t_cone) * header.cones_nb);
	scene->camera_x = header.camera_x;
	scene->camera_y = header.camera_y;
	scene->camera_z = header.camera_z;
	scene->materials_nb = header.materials_nb;
	scene->lights_nb = header.lights_nb;
	scene->planes_nb = header.planes_nb;
	scene->spheres_nb = header.spheres_nb;
	scene->cylinders_nb = header.cylinders_nb;
	scene->cones_nb = header.cones_nb;
		// if (read(fd, &header, 1))
		// {
		// 	write(1, error, sizeof(error) - 1);
		// 	exit(1);
		// }
}

void			delete_scene(t_scene scene)
{
	free(scene.planes);
	free(scene.spheres);
	free(scene.cylinders);
	free(scene.cones);
}