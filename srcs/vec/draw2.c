/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 22:38:26 by achazal           #+#    #+#             */
/*   Updated: 2016/03/08 22:38:32 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <mlx.h>
#include <mlx_macros.h>
#include <vec3.h>
#include <ray.h>
#include <math.h>
#include <forms.h>
#include <float.h>

void			draw_scene(t_data *data)
{
	t_window	window;

	if ((window.mlx_ptr = mlx_init()) == NULL)
		return ;
	if ((window.mlx_win = mlx_new_window(window.mlx_ptr, WIDTH, HEIGHT, NAME)) == NULL)
		return ;
	window.img = mlx_new_image(window.mlx_ptr, WIDTH, HEIGHT);
	window.data = mlx_get_data_addr(window.img, &(window.bpp),
		&(window.line_size), &(window.endian));
	raytrace(data, window);
	mlx_destroy_window(window.mlx_ptr, window.mlx_win);
}

int		main(int ac, char **av)
{
	t_data		*data;
	int			fd;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (0);
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
	init_scene(fd, &(data->scene));
	close(fd);
	if (VERBOSE)
		describe_scene(data->scene);
	draw_scene(data);
	delete_scene(data->scene);
	free(data);
	return (0);
}
