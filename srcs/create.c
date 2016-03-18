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

	h.camera_x = 0.1;
	h.camera_y = 1.0;
	h.camera_z = 2.1;
	h.materials_nb = 3;
	h.lights_nb = 2;
	h.planes_nb = 1;
	h.spheres_nb = 3;
	h.cylinders_nb = 0;
	h.cones_nb = 0;
	write(fd, &h, sizeof(h));
}

void	create_materials(int fd)
{
	t_material	m;

	m.r = 1.0;
	m.g = 1.0;
	m.b = 0.0;
	m.c = 0.5;
	add_element(fd, &m, sizeof(m));
	m.r = 0.0;
	m.b = 1.0;
	m.c = 1.5;
	add_element(fd, &m, sizeof(m));
	m.r = 1.0;
	m.g = 0.0;
	m.c = 0.0;
	add_element(fd, &m, sizeof(m));
}

void	create_lights(int fd)
{
	t_light		l;

	l.pos.x = 0.0;
	l.pos.y = 240.0;
	l.pos.z = -100.0;
	l.r = 1.0;
	l.g = 1.0;
	l.b = 1.0;
	add_element(fd, &l, sizeof(l));
	l.pos.x = 640.0;
	l.pos.z = -10000.0;
	l.r = 0.6;
	l.g = 0.7;
	l.b = 1.0;
	add_element(fd, &l, sizeof(l));
}

void	create_planes(int fd)
{
	t_plane	s;

	s.normal.x = 233.0;
	s.normal.y = 290.0;
	s.normal.z = 0.0;
	s.coord.x = 233.0;
	s.coord.y = 290.0;
	s.coord.z = 0.0;
	add_element(fd, &s, sizeof(s));
}

void	create_spheres(int fd)
{
	t_sphere	s;

	s.center.x = 233.0;
	s.center.y = 290.0;
	s.center.z = 0.0;
	s.r = 100;
	s.m = 0;
	add_element(fd, &s, sizeof(s));
	s.center.x = 407.0;
	s.center.y = 290.0;
	s.m = 1;
	add_element(fd, &s, sizeof(s));
	s.center.x = 320.0;
	s.center.y = 140.0;
	s.m = 2;
	add_element(fd, &s, sizeof(s));
}

void	create_cylinders(int fd)
{
	t_cylinder	s;

	s.x1 = 1.2;
	s.y1 = 2.3;
	s.z1 = 3.4;
	s.x2 = 4.5;
	s.y2 = 5.6;
	s.z2 = 6.7;
	s.r = 7.8;
	s.m = 0;
	add_element(fd, &s, sizeof(s));
	s.r = 5.5;
	add_element(fd, &s, sizeof(s));
	s.r = 6.5;
	add_element(fd, &s, sizeof(s));
}

void	create_cones(int fd)
{
	t_cone		s;

	s.x1 = 1.2;
	s.y1 = 2.3;
	s.z1 = 3.4;
	s.r1 = 7.8;
	s.x2 = 4.5;
	s.y2 = 5.6;
	s.z2 = 6.7;
	s.r2 = 8.9;
	s.m = 0;
	add_element(fd, &s, sizeof(s));
	s.r1 = 5.5;
	add_element(fd, &s, sizeof(s));
	s.r2 = 6.5;
	add_element(fd, &s, sizeof(s));
}

void	create_sceen(int fd)
{
	create_header(fd);
	create_materials(fd);
	create_lights(fd);
	create_planes(fd);
	create_spheres(fd);
	// create_cylinders(fd);
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
