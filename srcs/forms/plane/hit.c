#include <math.h>
#include <forms.h>

int				hit_plane(const t_ray ray, const t_plane plane, double *t)
{
	const double	dv = vec3_dot(plane.normal, ray.dir);
	double			tmp;

	if (dv == 0)
		return (0);
	tmp = (-vec3_dot(plane.normal, vec3_sub(ray.start, plane.coord))) / dv;
	if (tmp < 0 || tmp > *t)
		return (0);
	*t = tmp;
	return (1);
}

int				plane_normal(t_data *data)
{
	const t_plane	plane = data->scene.planes[data->closest[1]];
	const t_ray		ray = data->viewray;

	if (vec3_dot(plane.normal, ray.dir) < 0)
		data->normal = plane.normal;
	else
		data->normal = vec3_reverse(plane.normal);
	// data->material = data->scene.materials[data->scene.planes[data->closest[1]].m];
	data->material = data->scene.materials[data->scene.planes[data->closest[1]].m];
	data->new_start = vec3_add(data->viewray.start, vec3_mult(data->viewray.dir, data->t));
	return (1);
}

void			find_closest_plane(t_data *data, const t_ray ray, double *t)
{
	unsigned int			i;

	i = 0;
	while (i < data->scene.planes_nb)
	{
		if (hit_plane(ray, data->scene.planes[i], t))
		{
			data->closest[0] = PLANE;
			data->closest[1] = i;
		}
		++i;
	}
}

int				hit_any_plane(t_data *data, const t_ray ray, double t)
{
	unsigned int			i;

	i = 0;
	while (i < data->scene.planes_nb)
	{
		if (hit_plane(ray, data->scene.planes[i], &t))
			return (1);
		++i;
	}
	return (0);
}
