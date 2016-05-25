/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 22:38:26 by achazal           #+#    #+#             */
/*   Updated: 2016/03/08 22:38:32 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec3.h>
#include <stdio.h>
#include <math.h>

t_vec3				vec3_rotx(const t_vec3 vec, const double r)
{
	double			cos_r;
	double			sin_r;
	t_vec3			ret;

	if (!r)
		return (vec);
	cos_r = cos(r);
	sin_r = sin(r);
	ret.x = vec.x;
	ret.y = cos_r * vec.y - sin_r * vec.z;
	ret.z = sin_r * vec.y + cos_r * vec.z;
	return (ret);
}

t_vec3				vec3_roty(const t_vec3 vec, const double r)
{
	double			cos_r;
	double			sin_r;
	t_vec3			ret;

	if (!r)
		return (vec);
	cos_r = cos(r);
	sin_r = sin(r);
	ret.x = sin_r * vec.z + cos_r * vec.x;
	ret.y = vec.y;
	ret.z = cos_r * vec.z - sin_r * vec.x;
	return (ret);
}

t_vec3				vec3_rotz(const t_vec3 vec, const double r)
{
	double			cos_r;
	double			sin_r;
	t_vec3			ret;

	if (!r)
		return (vec);
	cos_r = cos(r);
	sin_r = sin(r);
	ret.x = cos_r * vec.x - sin_r * vec.y;
	ret.y = sin_r * vec.x + cos_r * vec.y;
	ret.z = vec.z;
	return (ret);
}
