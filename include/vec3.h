/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 22:38:26 by achazal           #+#    #+#             */
/*   Updated: 2016/03/08 22:38:32 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

typedef struct	s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

t_vec3			vec3_new(const double x, const double y, const double z);
t_vec3			vec3_reverse(const t_vec3 vec);
t_vec3			vec3_add(const t_vec3 vec1, const t_vec3 vec2);
t_vec3			vec3_sub(const t_vec3 vec1, const t_vec3 vec2);
t_vec3			vec3_mult(const t_vec3 vec, const double m);
double			vec3_dot(const t_vec3 vec1, const t_vec3 vec2);
t_vec3			vec3_cross(const t_vec3 vec1, const t_vec3 vec2);
double			vec3_len(const t_vec3 vec);
t_vec3			vec3_norm(const t_vec3 vec);
void			vec3_describe(const t_vec3 vec);
t_vec3			vec3_rotx(const t_vec3 vec, const double r);
t_vec3			vec3_roty(const t_vec3 vec, const double r);
t_vec3			vec3_rotz(const t_vec3 vec, const double r);

#endif
