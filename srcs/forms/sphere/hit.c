#include <math.h>
#include <forms.h>

int				hit_sphere(const t_ray ray, const t_sphere sphere, double *t)
{
	double	a;// a = pow(vector->x, 2) + pow(vector->y, 2) + pow(vector->z, 2);
	double	b;// b = 2 * (eye->x * vector->x + eye->y * vector->y + eye->z * vector->z);
	double	c;// c = pow(eye->x, 2) + pow(eye->y, 2) + pow(eye->z, 2) - pow(R, 2);
	double	delta;
	// const t_vec3	rayOrg = vec3_sub(sphere.center, ray.start);	// ray in space of the sphere
	const t_vec3	rayOrg = vec3_sub(ray.start, sphere.center);	// ray in space of the sphere

	// a = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y + ray.dir.z * ray.dir.z;
	a = vec3_dot(ray.dir, ray.dir);
	b = 2 * vec3_dot(ray.dir, rayOrg);
	// b = 2 * (rayOrg.x * ray.dir.x + rayOrg.y * ray.dir.y + rayOrg.z * ray.dir.z);
	// c = rayOrg.x * rayOrg.x + rayOrg.y * rayOrg.y + rayOrg.z * rayOrg.z - sphere.r * sphere.r;
	c = vec3_dot(rayOrg, rayOrg) - sphere.r * sphere.r;
	// delta = b * b - 4 * a * c;
	delta = b * b - 4 * a * c;
	// if (delta < 0)
	// 	return (0);
	if (delta == 0)
	{
		if (b >= 0)
		{
			*t = b;
			return (1);
		}
	}
	else if (delta >= 0)
	{
		delta = sqrt(delta);
		// c = (-b - delta) / 2 * a;
		// delta = (-b + delta) / 2 * a;
		c = (-b - delta) / 2 * a;
		delta = (-b + delta) / 2 * a;
		if (c >= 0 || delta >= 0)
		{
			*t = (c > delta) ? c : delta;
			return (1);
		}
	}
	return (0);


	// double	a;
	// double	b;
	// double	c;
	// double	delta;

	// a = vector->x * vector->x + vector->y * vector->y + vector->z * vector->z;
	// b = 2 * (eye->x * vector->x + eye->y * vector->y
	// 		+ eye->z * vector->z);
	// c = eye->x * eye->x + eye->y * eye->y + eye->z * eye->z - R * R;
	// delta = b * b - 4 * a * c;
	// if (delta >= 0)
	// {
	// 	delta = sqrt(delta);
	// 	c = (-b - delta) / 2 * a;
	// 	delta = (-b + delta) / 2 * a;
	// 	if (c >= 0 || delta >= 0)
	// 	{
	// 		*t = (c > delta) ? c : delta;
	// 		return (1);
	// 	}
	// }
	// return (0);



	// double			b, c;
	// double			delta;
	// double			t0;
	// double			t1;
	// const t_vec3	rayOrg = vec3_sub(sphere.center, ray.start);	// ray in space of the sphere

	// b = vec3_dot(ray.dir, rayOrg);
	// c = vec3_dot(rayOrg, rayOrg) - sphere.r * sphere.r;    
	// delta = b * b - c;

	// if (delta < 0.0f)
	// 	return 0; // pas d'intersection
	// if (delta != 0)
	// {
	// 	delta = sqrt(delta);
	// 	t0 = (b + delta);
	// 	t1 = (b - delta);
	// 	if (t0 < 0 || t1 < 0)
	// 		return (0);                                 
	// 	if (t0 > t1)
	// 		t0 = t1;
	// }                                  	
	// else 
	// 	t0 = b;
	// if (t0 < 0 || t0 > *t)
	// 	return (0);
	// *t = t0;
	// return (1);
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

	i = 0;
	while (i < data->scene.spheres_nb)
	{
		if (hit_sphere(ray, data->scene.spheres[i], &t))
			return (1);
		++i;
	}
	return (0);
}
