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

int				hit_cone(const t_ray ray, const t_cone cone, double *t)
{
	double			alpha;
	t_vec3			tmp1;
	t_vec3			origin;
	t_vec3			tmp2;

	alpha = cone.angle / 180 * M_PI;
	origin = vec3_sub(ray.start, cone.origin);
	tmp1 = vec3_sub(ray.dir, vec3_mult(cone.dir, vec3_dot(ray.dir, cone.dir)));
	tmp2 = vec3_sub(origin, vec3_mult(cone.dir, vec3_dot(origin, cone.dir)));
	return (solve_quadratic(pow(cos(alpha), 2) * vec3_dot(tmp1, tmp1) -
			pow(sin(alpha), 2) * pow(vec3_dot(ray.dir, cone.dir), 2),
		2 * (pow(cos(alpha), 2) * vec3_dot(tmp1, tmp2)) -
		2 * (pow(sin(alpha), 2) *
			vec3_dot(ray.dir, cone.dir) * vec3_dot(origin, cone.dir)),
		pow(cos(alpha), 2) * vec3_dot(tmp2, tmp2) - pow(sin(alpha), 2) *
			pow(vec3_dot(origin, cone.dir), 2),
		t));
}

int				cone_normal(t_data *data)
{
	const t_cone		cone = data->scene.cones[data->closest[1]];
	const t_ray			ray = data->viewray;
	t_vec3				intersect;

	intersect = vec3_add(ray.start, vec3_mult(ray.dir, data->t));
	data->normal = vec3_norm(vec3_sub(intersect, cone.origin));
	data->material = data->scene.materials[
							data->scene.cones[data->closest[1]].m];
	data->new_start = vec3_add(data->viewray.start,
						vec3_mult(data->viewray.dir, data->t));
	return (1);
}

void			find_closest_cone(t_data *data, const t_ray ray, double *t)
{
	unsigned int			i;

	i = 0;
	while (i < data->scene.cones_nb)
	{
		if (hit_cone(ray, data->scene.cones[i], t))
		{
			data->closest[0] = CONE;
			data->closest[1] = i;
		}
		++i;
	}
}

int				hit_any_cone(t_data *data, const t_ray ray, double t)
{
	unsigned int			i;

	i = 0;
	while (i < data->scene.cones_nb)
	{
		if (hit_cone(ray, data->scene.cones[i], &t))
			return (1);
		++i;
	}
	return (0);
}
