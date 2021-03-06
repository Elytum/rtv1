/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 22:38:26 by achazal           #+#    #+#             */
/*   Updated: 2016/03/08 22:38:32 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char		valid_scene(const t_header header)
{
	if (header.materials_nb > 10000 ||
		header.lights_nb > 10000 ||
		header.planes_nb > 10000 ||
		header.spheres_nb > 10000 ||
		header.cylinders_nb > 10000 ||
		header.cones_nb > 10000)
	{
		write(2, TOO_BIG, sizeof(TOO_BIG));
		return (0);
	}
	return (1);
}

static char		file_ended(const int fd)
{
	char		c;

	if (read(fd, &c, 1) == 0)
		return (1);
	write(2, EXTRA_DATA, sizeof(EXTRA_DATA));
	return (0);
}

void			init_scene(int fd, t_scene *scene)
{
	t_header	header;

	if (!(read(fd, &header, sizeof(header)) == sizeof(header)) ||
		!valid_scene(header))
		exit(0);
	scene->materials = extract_data(fd,
		sizeof(t_material) * header.materials_nb);
	scene->lights = extract_data(fd, sizeof(t_light) * header.lights_nb);
	scene->planes = extract_data(fd, sizeof(t_plane) * header.planes_nb);
	scene->spheres = extract_data(fd, sizeof(t_sphere) * header.spheres_nb);
	scene->cylinders = extract_data(fd,
		sizeof(t_cylinder) * header.cylinders_nb);
	scene->cones = extract_data(fd, sizeof(t_cone) * header.cones_nb);
	if (!file_ended(fd))
		exit(0);
	scene->camera_x = header.camera_x;
	scene->camera_y = header.camera_y;
	scene->camera_z = header.camera_z;
	scene->view = header.view;
	scene->materials_nb = header.materials_nb;
	scene->lights_nb = header.lights_nb;
	scene->planes_nb = header.planes_nb;
	scene->spheres_nb = header.spheres_nb;
	scene->cylinders_nb = header.cylinders_nb;
	scene->cones_nb = header.cones_nb;
}

void			delete_scene(t_scene scene)
{
	free(scene.planes);
	free(scene.spheres);
	free(scene.cylinders);
	free(scene.cones);
}
