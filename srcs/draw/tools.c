/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
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

void			init_data(t_data *data, int x, int y)
{
	t_vec3		target = vec3_norm(vec3_new(x - WIDTH / 2,
					y - HEIGHT / 2, - (WIDTH / 2 * tan(30 / 2))));

	data->color[0] = 0;
	data->color[1] = 0;
	data->color[2] = 0;
	data->coef = 1.0f;
	data->level = 0;
	data->once = 1;
	data->viewray.start = vec3_new(data->scene.camera_x,
					data->scene.camera_y, data->scene.camera_z);
	target = vec3_rotx(target, data->scene.view.x);
	target = vec3_roty(target, data->scene.view.y);
	target = vec3_rotz(target, data->scene.view.z - 1);
	data->viewray.dir = vec3_norm(target);
}	

int				find_normal(const t_ray viewray, const float t,
							t_vec3 *new_start, t_vec3 *n, t_vec3 center)
{
	float		temp;

	*new_start = vec3_add(viewray.start, vec3_mult(viewray.dir, t));
	*n = vec3_sub(*new_start, center);
	temp = vec3_dot(*n, *n);
	if (temp == 0.0f)
		return (0);
	*n = vec3_mult(*n, 1.0f / sqrt(temp));
	return (1);
}

int				rgb_color(int r, int g, int b)
{
	return ((r << 16) + (g << 8) + b);
}