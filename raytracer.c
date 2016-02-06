#include <raytracer.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#define PLANES_INTRO "Planes:\n"
#define SPHERES_INTRO "Spheres:\n"
#define CYLINDERS_INTRO "Cylinders:\n"
#define CONES_INTRO "Cones:\n"
#define FORMAT_INTRO "Wrong format: "
#define FORMAT_OUTRO " <OUTPUT FILE>\n"
#define OPEN_INTRO "Couldn't open file \""
#define OPEN_OUTRO "\"\n"
#define UNKNOWN "Unknown form, stopping\n"
#define VERBOSE 1

void	get_header(int fd, t_header *h)
{
	if (read(fd, h, sizeof(*h)) == sizeof(*h))
	{
		if (VERBOSE)
			printf("Camera: (%f, %f, %f)\nNumber of planes: %i\nNumber of spheres: %i\nNumber of cylinders: %i\nNumber of cones: %i\n\n",
					h->camera_x, h->camera_y, h->camera_z, h->planes_nb, h->spheres_nb, h->cylinders_nb, h->cones_nb);
	}
	else
		exit(0);
}

void	*safe_malloc(size_t size)
{
	const char	error[] = "Malloc error\n";
	void		*ret;

	if (!(ret = malloc(size)))
	{
		write(2, error, sizeof(error) - 1);
		exit(1);
	}
}

void	*extract_data(int fd, size_t size)
{
	const char	error[] = "Couldn't extract data\n";
	void		*ret;

	ret = safe_malloc(size);
	if (read(fd, ret, size) != size)
	{
		write(2, error, sizeof(error) - 1);
		exit(1);
	}
	return (ret);
}

void	init_scene(int fd, t_scene *scene)
{
	t_header	header;
	const char	error[] = "Extra data in map\n";

	get_header(fd, &header);
	scene->planes = extract_data(fd, sizeof(t_plane) * header.planes_nb);
	scene->spheres = extract_data(fd, sizeof(t_sphere) * header.spheres_nb);
	scene->cylinders = extract_data(fd, sizeof(t_cylinder) * header.cylinders_nb);
	scene->cones = extract_data(fd, sizeof(t_cone) * header.cones_nb);
	scene->camera_x = header.camera_x;
	scene->camera_y = header.camera_y;
	scene->camera_z = header.camera_z;
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

void	delete_scene(t_scene scene)
{
	free(scene.planes);
	free(scene.spheres);
	free(scene.cylinders);
	free(scene.cones);
}

void	draw_sceen(t_scene scene)
{
	(void)scene;
}

void	describe_planes(t_scene scene)
{
	int	i;

	write(1, PLANES_INTRO, sizeof(PLANES_INTRO) - 1);
	i = 0;
	while (i < scene.planes_nb)
	{
		printf("\t(%f, %f, %f)\n", scene.planes[i].x, scene.planes[i].y, scene.planes[i].z);
		++i;
	}
}

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

void	describe_cones(t_scene scene)
{
	int	i;

	write(1, CONES_INTRO, sizeof(PLANES_INTRO) - 1);
	i = 0;
	while (i < scene.cones_nb)
	{
		printf("\t(%f, %f, %f) %f (%f, %f, %f) %f\n",
				scene.cones[i].x1, scene.cones[i].y1, scene.cones[i].z1,
				scene.cones[i].r1, scene.cones[i].x2, scene.cones[i].y2,
				scene.cones[i].z2, scene.cones[i].r2);
		++i;
	}
}

void	descibe_scene(t_scene scene)
{

	if (scene.planes_nb)
		describe_planes(scene);
	if (scene.spheres_nb)
		describe_spheres(scene);
	if (scene.cylinders_nb)
		describe_cylinders(scene);
	if (scene.cones_nb)
		describe_cones(scene);
}

int		main(int ac, char **av)
{
	t_scene		scene;
	int			fd;

	if (ac != 2)
	{
		write(2, FORMAT_INTRO, sizeof(FORMAT_INTRO) - 1);
		write(2, av[0], strlen(av[0]));
		write(2, FORMAT_OUTRO, sizeof(FORMAT_OUTRO) - 1);
		return (1);
	}
	if ((fd = open(av[1], O_RDONLY | O_CREAT)) == -1)
	{
		write(2, OPEN_INTRO, sizeof(OPEN_INTRO) - 1);
		write(2, av[1], strlen(av[1]));
		write(2, OPEN_OUTRO, sizeof(OPEN_OUTRO) - 1);
		return (1);
	}
	init_scene(fd, &scene);
	close(fd);
	draw_sceen(scene);
	descibe_scene(scene);
	delete_scene(scene);
	return (0);
}