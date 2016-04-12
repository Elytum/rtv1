/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabtoubl <gabtoubl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/13 16:26:35 by gabtoubl          #+#    #+#             */
/*   Updated: 2014/02/15 00:46:07 by gabtoubl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<math.h>
#include	"rtv1.h"

void		calc_sphere(t_xyz *eye, t_xyz *vector, double *k)
{
	double	a;
	double	b;
	double	c;
	double	delta;

	a = pow(vector->x, 2) + pow(vector->y, 2) + pow(vector->z, 2);
	b = 2 * (eye->x * vector->x + eye->y * vector->y
			+ eye->z * vector->z);
	c = pow(eye->x, 2) + pow(eye->y, 2)
		+ pow(eye->z, 2) - pow(R, 2);
	delta = pow(b, 2) - 4 * a * c;
	k[0] = (delta >= 0 ? (-b - sqrt(delta)) / (2 * a) : -1);
	k[1] = (delta >= 0 ? (-b + sqrt(delta)) / (2 * a) : -1);
}

void		calc_cylinder(t_xyz *eye, t_xyz *vector, double *k)
{
	double	a;
	double	b;
	double	c;
	double	delta;

	a = pow(vector->x, 2) + pow(vector->y, 2);
	b = 2 * (eye->x * vector->x + eye->y * vector->y);
	c = pow(eye->x, 2) + pow(eye->y, 2) - pow(R / 1.5, 2);
	delta = pow(b, 2) - 4 * a * c;
	k[0] = (delta >= 0 ? (-b - sqrt(delta)) / (2 * a) : -1);
	k[1] = (delta >= 0 ? (-b + sqrt(delta)) / (2 * a) : -1);
}

void		calc_cone(t_xyz *eye, t_xyz *vector, double *k)
{
	double	new_z;
	double	a;
	double	b;
	double	c;
	double	delta;

	new_z = 0.7 * vector->z;
	a = pow(vector->x, 2) + pow(vector->y, 2) - pow(new_z, 2);
	b = 2 * (eye->x * vector->x + eye->y * vector->y
			- eye->z * new_z);
	c = pow(eye->x, 2) + pow(eye->y, 2)
		- pow(eye->z, 2);
	delta = pow(b, 2) - 4 * a * c;
	k[0] = (delta >= 0 ? (-b - sqrt(delta)) / (2 * a) : -1);
	k[1] = (delta >= 0 ? (-b + sqrt(delta)) / (2 * a) : -1);
}

void		calc_plan(t_xyz *eye, t_xyz *vector, double *k)
{
	if (vector->z < 0.000001 && vector->z > -0.000001)
		k[0] = -1;
	else
		k[0] = -eye->z / vector->z;
	k[1] = -1;
}
