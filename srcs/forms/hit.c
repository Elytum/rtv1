/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 22:38:26 by achazal           #+#    #+#             */
/*   Updated: 2016/03/08 22:38:32 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forms.h>
#include <math.h>

int			find_closest(t_data *data, const int get_normal)
{
	data->closest[1] = -1;
	if (get_normal == 1)
	{
		find_closest_sphere(data, data->viewray, &(data->t));
		find_closest_plane(data, data->viewray, &(data->t));
		find_closest_cone(data, data->viewray, &(data->t));
		find_closest_cylinder(data, data->viewray, &(data->t));
		if (data->closest[1] == -1)
			return (0);
		if (data->closest[0] == SPHERE)
			return (sphere_normal(data));
		else if (data->closest[0] == PLANE)
			return (plane_normal(data));
		else if (data->closest[0] == CYLINDER)
			return (cylinder_normal(data));
		else if (data->closest[0] == CONE)
			return (cone_normal(data));
		return (1);
	}
	return (hit_any_sphere(data, data->lightray, data->t) ||
			hit_any_plane(data, data->lightray, data->t) ||
			hit_any_cone(data, data->lightray, data->t) ||
			hit_any_cylinder(data, data->lightray, data->t));
}

static int	solve_quadratic_extended(double delta, double b, double *t)
{
	if (delta < 0)
		return (0);
	else if (*t < b && b > .1)
	{
		*t = b;
		return (1);
	}
	return (0);
}

int			solve_quadratic(double a, double b, double c, double *t)
{
	double delta;
	double x0;
	double x1;
	double q;

	delta = b * b - 4 * a * c;
	if (delta > 0)
	{
		q = (b > 0) ? -.5 * (b + sqrt(delta)) : -.5 * (b + sqrt(delta));
		x0 = q / a;
		x1 = c / q;
		if (x0 > x1)
			x0 = x1;
		if (*t > x0 && x0 > 0.1)
		{
			*t = x0;
			return (1);
		}
	}
	else
		return (solve_quadratic_extended(delta, b, t));
	return (0);
}
