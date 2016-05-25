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

int				hit_sphere(const t_ray ray, const t_sphere sphere, double *t)
{
	const t_vec3	rayorg = vec3_sub(ray.start, sphere.center);

	return (solve_quadratic(vec3_dot(ray.dir, ray.dir),
		2 * vec3_dot(ray.dir, rayorg),
		vec3_dot(rayorg, rayorg) - sphere.r * sphere.r,
		t));
}

int				sphere_normal(t_data *data)
{
	const t_sphere	sphere = data->scene.spheres[data->closest[1]];
	const t_ray		ray = data->viewray;
	t_vec3			intersect;

	intersect = vec3_add(ray.start, vec3_mult(ray.dir, data->t));
	data->normal = vec3_norm(vec3_sub(intersect, sphere.center));
	data->material = data->scene.materials[
						data->scene.spheres[data->closest[1]].m];
	data->new_start = vec3_add(data->viewray.start,
							vec3_mult(data->viewray.dir, data->t));
	return (1);
}

void			find_closest_sphere(t_data *data, const t_ray ray, double *t)
{
	unsigned int			i;

	i = 0;
	while (i < data->scene.spheres_nb)
	{
		if (hit_sphere(ray, data->scene.spheres[i], t))
		{
			data->closest[0] = SPHERE;
			data->closest[1] = i;
		}
		++i;
	}
}

int				hit_any_sphere(t_data *data, const t_ray ray, double t)
{
	unsigned int			i;

	i = 0;
	while (i < data->scene.spheres_nb)
	{
		if (hit_sphere(ray, data->scene.spheres[i], &t))
			return (1);
		++i;
	}
	return (0);
}
