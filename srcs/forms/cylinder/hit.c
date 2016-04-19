#include <math.h>
#include <forms.h>
#include <ray.h>
	
int				hit_cylinder(const t_ray ray, const t_cylinder cylinder, double *t)
{
	float			a;
	float			b;
	float			c;
	float			delta;
	float			dist1;
	float			dist2;
	t_vec3			tmp1;
	t_vec3			origin;
	t_vec3			tmp2;

	origin = vec3_sub(ray.start, cylinder.origin);
	tmp1 = vec3_sub(ray.dir, vec3_mult(cylinder.dir, vec3_dot(ray.dir, cylinder.dir)));
	tmp2 = vec3_sub(origin, vec3_mult(cylinder.dir, vec3_dot(origin, cylinder.dir)));
	a = vec3_dot(tmp1, tmp1);
	b = 2 * vec3_dot(tmp1, tmp2);
	c = vec3_dot(tmp2, tmp2) - cylinder.r * cylinder.r;
	if ((delta = b * b - (4 * a * c)) < 0)
		return (0);
	else
	{
		dist1 = (b * -1.0 + sqrt(delta)) / (2.0 * a);
		dist2 = (b * -1.0 - sqrt(delta)) / (2.0 * a);
		if (dist1 < 0.1 && dist2 < 0.1)
			return (0);
		else if (dist1 >= 0.1 && dist2 >= 0.1)
			dist1 = dist2;
		if (dist1 >= 0.1 && dist1 < *t)
		{
			*t = dist1;
			return (1);
		}
	}
	return (0);
}

int				cylinder_normal(t_data *data)
{
	const t_cylinder	cylinder = data->scene.cylinders[data->closest[1]];
	const t_ray			ray = data->viewray;
	t_vec3				intersect;

	intersect = vec3_add(ray.start, vec3_mult(ray.dir, data->t));
	data->normal = vec3_norm(vec3_sub(vec3_new(intersect.x, 0, intersect.z), vec3_new(cylinder.origin.x, 0, cylinder.origin.z)));
	data->material = data->scene.materials[data->scene.cylinders[data->closest[1]].m];
	data->new_start = vec3_add(data->viewray.start, vec3_mult(data->viewray.dir, data->t));
	return 1;
}

void			find_closest_cylinder(t_data *data, const t_ray ray, double *t)
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

int				hit_any_cylinder(t_data *data, const t_ray ray, double t)
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
