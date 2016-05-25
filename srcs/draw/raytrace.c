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

void			handle_lights(t_data *data, t_light current)
{
	double	lambert;
	double	ratio;
	double	dot;
	t_vec3	r;

	lambert = vec3_dot(data->lightray.dir, data->normal) * data->coef;
	data->color[0] += lambert * current.r * data->material.r;
	data->color[1] += lambert * current.g * data->material.g;
	data->color[2] += lambert * current.b * data->material.b;

	r = vec3_sub(data->lightray.dir, vec3_mult(data->normal,
				2 * vec3_dot(data->lightray.dir, data->normal)));
	dot = vec3_dot(data->viewray.dir, r);
	if (dot > 0)
	{
		ratio = 1 * pow(dot, 20);
		data->color[0] += ratio * current.r;
		data->color[1] += ratio * current.g;
		data->color[2] += ratio * current.b;
	}
}

void			iterate_lights(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->scene.lights_nb)
	{
		t_light		current = data->scene.lights[i];
		t_vec3		dist = vec3_sub(current.pos, data->new_start);

		if (vec3_dot(data->normal, dist) <= 0.0f)
		{
			++i;
			continue ;
		}
		data->t = sqrt(vec3_dot(dist, dist));
		if (data->t <= 0.0f)
		{
			++i;
			continue ;
		}
		data->lightray.start = data->new_start;
		data->lightray.dir = vec3_mult(dist, 1 / data->t);
		if (!find_closest(data, 0))
			handle_lights(data, current);
		++i;
	}
}

int				get_color(t_data *data, int x, int y)
{

	init_data(data, x, y);
	while (data->once || (data->coef > 0.0f && data->level < 2))
	{
		data->once = 0;
		data->t = DBL_MAX;
		if (!find_closest(data, 1))
			break ;
		double reflet = 2.0f * vec3_dot(data->viewray.dir, data->normal);
		iterate_lights(data);
		data->coef *= data->material.c;
		data->viewray.start = data->new_start;
		data->viewray.start = data->new_start;
		data->viewray.dir = vec3_sub(data->viewray.dir, vec3_mult(data->normal, reflet));
		++data->level;
	}
	return (rgb_color(MIN(data->color[0] * 255.0f, 255.0f), MIN(data->color[1] * 255.0f, 255.0f), MIN(data->color[2] * 255.0f, 255)));
}

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