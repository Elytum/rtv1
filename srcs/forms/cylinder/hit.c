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

#include <math.h>
#include <forms.h>
#include <ray.h>

int			hit_cylinder(const t_ray ray, const t_cylinder cylinder, double *t)
{
	t_vec3	tmp1;
	t_vec3	origin;
	t_vec3	tmp2;

	origin = vec3_sub(ray.start, cylinder.origin);
	tmp1 = vec3_sub(ray.dir, vec3_mult(cylinder.dir,
				vec3_dot(ray.dir, cylinder.dir)));
	tmp2 = vec3_sub(origin, vec3_mult(cylinder.dir,
				vec3_dot(origin, cylinder.dir)));
	return (solve_quadratic(vec3_dot(tmp1, tmp1),
		2 * vec3_dot(tmp1, tmp2),
		vec3_dot(tmp2, tmp2) - cylinder.r * cylinder.r,
		t));
}

int			cylinder_normal(t_data *data)
{
	const t_cylinder	cylinder = data->scene.cylinders[data->closest[1]];
	const t_ray			ray = data->viewray;
	t_vec3				intersect;

	intersect = vec3_add(ray.start, vec3_mult(ray.dir, data->t));
	data->normal = vec3_norm(vec3_sub(vec3_new(intersect.x, 0, intersect.z),
							vec3_new(cylinder.origin.x, 0, cylinder.origin.z)));
	data->material = data->scene.materials[
							data->scene.cylinders[data->closest[1]].m];
	data->new_start = vec3_add(data->viewray.start,
						vec3_mult(data->viewray.dir, data->t));
	return (1);
}

void		find_closest_cylinder(t_data *data, const t_ray ray, double *t)
{
	unsigned int			i;

	i = 0;
	while (i < data->scene.cylinders_nb)
	{
		if (hit_cylinder(ray, data->scene.cylinders[i], t))
		{
			data->closest[0] = CYLINDER;
			data->closest[1] = i;
		}
		++i;
	}
}

int			hit_any_cylinder(t_data *data, const t_ray ray, double t)
{
	unsigned int			i;

	i = 0;
	while (i < data->scene.cylinders_nb)
	{
		if (hit_cylinder(ray, data->scene.cylinders[i], &t))
			return (1);
		++i;
	}
	return (0);
}
