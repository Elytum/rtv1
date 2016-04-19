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
	h.camera_z = -100.0;
	h.view = vec3_norm(vec3_new(0, 0, 1));
	h.materials_nb = 4;
	h.lights_nb = 3;
	h.planes_nb = 3;
	h.spheres_nb = 8;
	h.cylinders_nb = 4;
	h.cylinders_finite_nb = 0;
	h.cones_nb = 0;
	write(fd, &h, sizeof(h));
}

void	create_materials(int fd)
{
	t_material	m;

	/* Back Wall */
	m.c = 0;
	m.r = .3;
	m.g = .3;
	m.b = 1.0;
	add_element(fd, &m, sizeof(m));

	/* Top Wall */
	m.c = 0;
	m.r = .175;
	m.g = .175;
	m.b = .175;
	add_element(fd, &m, sizeof(m));

	/* Bottom Wall */
	m.c = 0;
	m.r = .65;
	m.g = .65;
	m.b = .65;
	add_element(fd, &m, sizeof(m));

	/* Cylinders and balls */
	m.c = .5;
	m.r = .75;
	m.g = .75;
	m.b = .75;
	add_element(fd, &m, sizeof(m));
}

void	create_lights(int fd)
{
	t_light		l;

	l.pos.x = -100.0;
	l.pos.y = 0.0;
	l.pos.z = -100.0;
	l.r = 1.0;
	l.g = 1.0;
	l.b = 1.0;
	add_element(fd, &l, sizeof(l));
	l.pos.x = 100.0;
	l.pos.y = 0.0;
	l.pos.z = -100.0;
	l.r = 0.6;
	l.g = 0.7;
	l.b = 1.0;
	add_element(fd, &l, sizeof(l));
	l.pos.x = 0.0;
	l.pos.y = 1500.0;
	l.pos.z = -5000.0;
	l.r = 0.6;
	l.g = 0.7;
	l.b = 1.0;
	add_element(fd, &l, sizeof(l));
}

void	create_planes(int fd)
{
	t_plane	s;

	/* Back wall */
	s.m = 0;
	s.normal = vec3_norm(vec3_new(0, 0, 1));
	s.coord.x = 0.0;
	s.coord.y = 0.0;
	s.coord.z = 70.0;
	add_element(fd, &s, sizeof(s));

	/* Top wall */
	s.m = 1;
	s.normal = vec3_norm(vec3_new(0, 1, 0));
	s.coord.x = 0.0;
	s.coord.y = -50.0;
	s.coord.z = 70.0;
	add_element(fd, &s, sizeof(s));

	/* Bottom wall */
	s.m = 2;
	s.normal = vec3_norm(vec3_new(0, 1, 0));
	s.coord.x = 0.0;
	s.coord.y = 50.0;
	s.coord.z = 70.0;
	add_element(fd, &s, sizeof(s));
}

void	create_spheres(int fd)
{
	t_sphere	s;

	/* First top */
	s.m = 3;
	s.r = 20;
	s.center.x = -75;
	s.center.y = -50.0;
	s.center.z = 0.0;
	add_element(fd, &s, sizeof(s));

	/* First bottom */
	s.m = 3;
	s.r = 20;
	s.center.x = -75;
	s.center.y = 50.0;
	s.center.z = 0.0;
	add_element(fd, &s, sizeof(s));

	/* Second top */
	s.m = 3;
	s.r = 20;
	s.center.x = 75;
	s.center.y = -50.0;
	s.center.z = 0.0;
	add_element(fd, &s, sizeof(s));

	/* Second bottom */
	s.m = 3;
	s.r = 20;
	s.center.x = 75;
	s.center.y = 50.0;
	s.center.z = 0.0;
	add_element(fd, &s, sizeof(s));

	/* Third top */
	s.m = 3;
	s.r = 20;
	s.center.x = -50;
	s.center.y = -50.0;
	s.center.z = 50;
	add_element(fd, &s, sizeof(s));

	/* Third bottom */
	s.m = 3;
	s.r = 20;
	s.center.x = -50;
	s.center.y = 50.0;
	s.center.z = 50;
	add_element(fd, &s, sizeof(s));

	/* Fourth top */
	s.m = 3;
	s.r = 20;
	s.center.x = 50;
	s.center.y = -50.0;
	s.center.z = 50;
	add_element(fd, &s, sizeof(s));

	/* Fourth bottom */
	s.m = 3;
	s.r = 20;
	s.center.x = 50;
	s.center.y = 50.0;
	s.center.z = 50;
	add_element(fd, &s, sizeof(s));
}

void	create_cylinders(int fd)
{
	t_cylinder	s;

	/* First */
	s.dir = vec3_norm(vec3_new(0, 1, 0));
	s.m = 3;
	s.r = 10;
	s.origin.x = -75;
	s.origin.y = 0;
	s.origin.z = 0;
	add_element(fd, &s, sizeof(s));

	/* Second */
	s.dir = vec3_norm(vec3_new(0, 1, 0));
	s.m = 3;
	s.r = 10;
	s.origin.x = 75;
	s.origin.y = 0;
	s.origin.z = 0;
	add_element(fd, &s, sizeof(s));

	/* Third */
	s.dir = vec3_norm(vec3_new(0, 1, 0));
	s.m = 3;
	s.r = 10;
	s.origin.x = -50;
	s.origin.y = 0;
	s.origin.z = 50;
	add_element(fd, &s, sizeof(s));

	/* Fourth */
	s.dir = vec3_norm(vec3_new(0, 1, 0));
	s.m = 3;
	s.r = 10;
	s.origin.x = 50;
	s.origin.y = 0;
	s.origin.z = 50;
	add_element(fd, &s, sizeof(s));
}

void	create_cylinders_finite(int fd)
{
	(void)fd;
}

void	create_cones(int fd)
{
	(void)fd;
	// t_cone		s;

	// s.x1 = 1.2;
	// s.y1 = 2.3;
	// s.z1 = 3.4;
	// s.r1 = 7.8;
	// s.x2 = 4.5;
	// s.y2 = 5.6;
	// s.z2 = 6.7;
	// s.r2 = 8.9;
	// s.m = 0;
	// add_element(fd, &s, sizeof(s));
}

void	create_sceen(int fd)
{
	create_header(fd);
	create_materials(fd);
	create_lights(fd);
	create_planes(fd);
	create_spheres(fd);
	create_cylinders(fd);
	// create_cylinders_finite(fd);
	// create_cones(fd);
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
