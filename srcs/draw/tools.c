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