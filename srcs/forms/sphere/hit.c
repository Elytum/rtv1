#include <math.h>
#include <forms.h>

int				hit_sphere(const t_ray ray, const t_sphere sphere, double *t)
{
	double			b, c;
	double			delta;
	double			t0;
	double			t1;
	const t_vec3	rayOrg = vec3_sub(sphere.center, ray.start);	// ray in space of the sphere

	b = vec3_dot(ray.dir, rayOrg);
	c = vec3_dot(rayOrg, rayOrg) - sphere.r * sphere.r;    
	delta = b * b - vec3_dot(rayOrg, rayOrg) + sphere.r * sphere.r;

	if (delta < 0.0f)
		return 0; // pas d'intersection
	if (delta != 0)
	{
		delta = sqrt(delta);
		t0 = (b + delta);
		t1 = (b - delta);
		if (t0 < 0 || t1 < 0)
			return (0);                                 
		if (t0 > t1)
			t0 = t1;
	}                                  	
	else 
		t0 = b;
	if (t0 < 0 || t0 > *t)
		return (0);
	// if (t0 < *t)
	// {
	// printf("\t\tt0: %f\n", t0);
	*t = t0;
	return (1);
	// }
	// return (0);
}

int				sphere_normal(t_data *data)
{
	const t_sphere	sphere = data->scene.spheres[data->closest[1]];
	const t_ray		ray = data->viewray;
	t_vec3			intersect;

	intersect = vec3_add(ray.start, vec3_mult(ray.dir, data->t));
	data->normal = vec3_norm(vec3_mult(vec3_sub(intersect, sphere.center), 1 / sphere.r));
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

	i = 0;
	while (i < data->scene.spheres_nb)
	{
		if (hit_sphere(ray, data->scene.spheres[i], &t))
			return (1);
		++i;
	}
	return (0);
}
