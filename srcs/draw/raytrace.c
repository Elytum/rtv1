/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
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

void			raytrace(t_data *data, t_window window)
{
	int			x;
	int			y;
	int			color;
	char		*ptr;
	int			*cast;

	while (42)
	{
		ptr = window.data;
		y = 0;
		while (y < HEIGHT)
		{
			x = 0;
			while (x < WIDTH)
			{
				color = get_color(data, x, y);
				cast = (int *)ptr;
				*cast = color;
				++x;
				ptr += 4;
			}
			++y;
		}
		mlx_put_image_to_window(window.mlx_ptr,
			window.mlx_win, window.img, 0, 0);
		mlx_do_sync(window.mlx_ptr);
	}
}