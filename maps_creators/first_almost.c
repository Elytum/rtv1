#include <raytracer.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define FORMAT_INTRO "Wrong format: "
#define FORMAT_OUTRO " <OUTPUT FILE>\n"
#define OPEN_INTRO "Couldn't open file \""
#define OPEN_OUTRO "\"\n"

void	add_element(int fd, const void *form, int size)
{
	write(fd, form, size);
}

void	create_header(int fd)
{
	t_header	h;

	h.camera_x = 0.0;
	h.camera_y = 0.0;
	h.camera_z = -10.0;
	h.view = vec3_norm(vec3_new(0, 0, 1));
	h.materials_nb = 2;
	h.lights_nb = 1;
	h.planes_nb = 1;
	h.spheres_nb = 0;
	h.cylinders_nb = 0;
	h.cylinders_finite_nb = 0;
	h.cones_nb = 1;
	write(fd, &h, sizeof(h));
}

void	create_materials(int fd)
{
	t_material	m;

	/* Sphere */
	m.c = 0;
	m.r = 1;
	m.g = 0;
	m.b = 0;
	add_element(fd, &m, sizeof(m));
}

void	create_lights(int fd)
{
	t_light		l;

	l.pos.x = 10.0;
	l.pos.y = 0;
	l.pos.z = -10;
	l.r = 1.0;
	l.g = 1.0;
	l.b = 1.0;
	add_element(fd, &l, sizeof(l));
}

void	create_planes(int fd)
{
	(void)fd;
}

void	create_spheres(int fd)
{
	t_sphere	s;

	/* Sphere */
	s.m = 3;
	s.r = 20;
	s.center.x = -60;
	s.center.y = -50.0;
	s.center.z = -25.0;
	add_element(fd, &s, sizeof(s));
}

void	create_cylinders(int fd)
{
	(void)fd;
}

void	create_cylinders_finite(int fd)
{
	(void)fd;
}

void	create_cones(int fd)
{
	(void)fd;
}

void	create_sceen(int fd)
{
	create_header(fd);
	create_materials(fd);
	// create_lights(fd);
	// create_planes(fd);
	create_spheres(fd);
	// create_cylinders(fd);
	// create_cylinders_finite(fd);
	create_cones(fd);
}

int		main(int ac, char **av)
{
	int		fd;

	if (ac != 2)
	{
		write(2, FORMAT_INTRO, sizeof(FORMAT_INTRO) - 1);
		write(2, av[0], strlen(av[0]));
		write(2, FORMAT_OUTRO, sizeof(FORMAT_OUTRO) - 1);
		return (1);
	}
	if ((fd = open(av[1], O_WRONLY | O_CREAT)) == -1)
	{
		write(2, OPEN_INTRO, sizeof(OPEN_INTRO) - 1);
		write(2, av[1], strlen(av[1]));
		write(2, OPEN_OUTRO, sizeof(OPEN_OUTRO) - 1);
		return (1);
	}
	create_sceen(fd);
	close(fd);
	return (0);
}
