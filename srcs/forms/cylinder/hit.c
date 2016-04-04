#include <math.h>
#include <forms.h>

int				hit_cylinder(const t_ray ray, const t_cylinder cylinder, double *t)
{
	return (0);
	(void)ray;
	(void)cylinder;
	(void)t;
	// t_vec3		dist;
	// float		b;
	// float		d;
	// float		t0;
	// float		t1;
	// int			ret;

	// dist = vec3_sub(sphere.center, ray.start);
	// b = vec3_dot(ray.dir, dist);
	// d = b * b - vec3_dot(dist, dist) + sphere.r * sphere.r;
	// t0 = b - sqrt(d);
	// t1 = b + sqrt(d);
	// ret = 0;
	// if (t0 > 1 && t0 < *t)
	// {
	// 	*t = t0;
	// 	ret = 1;
	// }
	// if (t1 > 1 && t1 < *t)
	// {
	// 	*t = t1;
	// 	ret = 1;
	// }
	// return (ret);
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
