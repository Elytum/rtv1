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

int				refresh(t_window *window)
{
	mlx_put_image_to_window(window->mlx_ptr,
			window->mlx_win, window->img, 0, 0);
	mlx_do_sync(window->mlx_ptr);
	return (0);
}

void			draw_scene(t_data *data)
{
	if ((data->window.mlx_ptr = mlx_init()) == NULL)
		return ;
	if ((data->window.mlx_win = mlx_new_window(data->window.mlx_ptr,
			WIDTH, HEIGHT, NAME)) == NULL)
		return ;
	data->window.img = mlx_new_image(data->window.mlx_ptr, WIDTH, HEIGHT);
	data->window.data = mlx_get_data_addr(data->window.img, &(data->window.bpp),
		&(data->window.line_size), &(data->window.endian));
	raytrace(data);
	mlx_expose_hook(data->window.mlx_win, refresh, &data->window);
	mlx_loop(data->window.mlx_ptr);
	mlx_destroy_window(data->window.mlx_ptr, data->window.mlx_win);
}

int				stop(t_data *data)
{
	delete_scene(data->scene);
	free(data);
	return (0);
}

int				main(int ac, char **av)
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
	if ((fd = open(av[1], O_RDONLY)) == -1)
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
	return (stop(data));
}
