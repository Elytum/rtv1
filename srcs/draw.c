#include <raytracer.h>

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
	if (VERBOSE)
		descibe_scene(scene);
	delete_scene(scene);
	return (0);
}