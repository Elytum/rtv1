#include <math.h>
#include <forms.h>

int				hit_sphere(const t_ray ray, const t_sphere sphere, double *t)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	const t_vec3	rayOrg = vec3_sub(ray.start, sphere.center);	// ray in space of the sphere

	a = vec3_dot(ray.dir, ray.dir);
	b = 2 * vec3_dot(ray.dir, rayOrg);
	c = vec3_dot(rayOrg, rayOrg) - sphere.r * sphere.r;

	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (0);
	else if (delta == 0)
	{
		if (*t > b && b > 0)
		{
			*t = b;
			return (1);
		}
	}
	else
	{
		double x0, x1;
		double q = (b > 0) ? -.5 * (b + sqrt(delta)) : -.5 * (b + sqrt(delta));
		x0 = q / a;
		x1 = c / q;
		if (x0 > x1)
			x0 = x1;
		if (*t > x0 && x0 > 0)
		{
			*t = x0;
			return (1);
		}
	}
	return (0);

}

int				sphere_normal(t_data *data)
{
	const t_sphere	sphere = data->scene.spheres[data->closest[1]];
	const t_ray		ray = data->viewray;
	t_vec3			intersect;

	intersect = vec3_add(ray.start, vec3_mult(ray.dir, data->t));
	data->normal = vec3_norm(vec3_sub(intersect, sphere.center));
	data->material = data->scene.materials[data->scene.spheres[data->closest[1]].m];
	data->new_start = vec3_add(data->viewray.start, vec3_mult(data->viewray.dir, data->t));
	return 1;
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

	// return (0);
	i = 0;
	while (i < data->scene.spheres_nb)
	{
		if (hit_sphere(ray, data->scene.spheres[i], &t))
			return (1);
		++i;
	}
	return (0);
}
