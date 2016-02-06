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
	h.planes_nb = 3;
	h.spheres_nb = 3;
	h.cylinders_nb = 3;
	h.cones_nb = 3;
	write(fd, &h, sizeof(h));
}

void	create_planes(int fd)
{
	t_plane	s;

	s.x = 1.2;
	s.y = 2.3;
	s.z = 3.4;
	add_element(fd, &s, sizeof(s));
	s.y = 5.5;
	add_element(fd, &s, sizeof(s));
	s.x = 6.5;
	add_element(fd, &s, sizeof(s));
}

void	create_spheres(int fd)
{
	t_sphere	s;

	s.x = 1.2;
	s.y = 2.3;
	s.z = 3.4;
	s.r = 4.5;
	add_element(fd, &s, sizeof(s));
	s.r = 5.5;
	add_element(fd, &s, sizeof(s));
	s.r = 6.5;
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
	add_element(fd, &s, sizeof(s));
	s.r1 = 5.5;
	add_element(fd, &s, sizeof(s));
	s.r2 = 6.5;
	add_element(fd, &s, sizeof(s));
}

void	create_sceen(int fd)
{
	create_header(fd);
	create_planes(fd);
	create_spheres(fd);
	create_cylinders(fd);
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
