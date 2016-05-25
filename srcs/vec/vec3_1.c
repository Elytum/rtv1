/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
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

double				vec3_dot(const t_vec3 vec1, const t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vec3				vec3_cross(const t_vec3 vec1, const t_vec3 vec2)
{
	t_vec3			ret;

	ret.x = vec1.x * vec2.x;
	ret.y = vec1.y * vec2.y;
	ret.z = vec1.z * vec2.z;
	return (ret);
}

double				vec3_len(const t_vec3 vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vec3				vec3_norm(const t_vec3 vec)
{
	const double	len = vec3_len(vec);
	t_vec3			ret;

	ret.x = vec.x / len;
	ret.y = vec.y / len;
	ret.z = vec.z / len;
	return (ret);
}

void				vec3_describe(const t_vec3 vec)
{
	dprintf(1, "(%f %f %f)", vec.x, vec.y, vec.z);
}
