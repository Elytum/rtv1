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

t_vec3			vec3_new(const double x, const double y, const double z)
{
	t_vec3		ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_vec3			vec3_reverse(const t_vec3 vec)
{
	t_vec3		ret;

	ret.x = -vec.x;
	ret.y = -vec.y;
	ret.z = -vec.z;
	return (ret);
}

t_vec3			vec3_add(const t_vec3 vec1, const t_vec3 vec2)
{
	t_vec3		ret;

	ret.x = vec1.x + vec2.x;
	ret.y = vec1.y + vec2.y;
	ret.z = vec1.z + vec2.z;
	return (ret);
}

t_vec3			vec3_sub(const t_vec3 vec1, const t_vec3 vec2)
{
	t_vec3		ret;

	ret.x = vec1.x - vec2.x;
	ret.y = vec1.y - vec2.y;
	ret.z = vec1.z - vec2.z;
	return (ret);
}

t_vec3			vec3_mult(const t_vec3 vec, const double m)
{
	t_vec3		ret;

	ret.x = vec.x * m;
	ret.y = vec.y * m;
	ret.z = vec.z * m;
	return (ret);
}
