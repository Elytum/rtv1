#include <math.h>
#include <forms.h>
//https://github.com/mmp/pbrt-v2/blob/master/src/shapes/cylinder.cpp

char	Quadratic(float A, float B, float C, float *t0, float *t1) {
    // Find quadratic discriminant
    float discrim = B * B - 4.f * A * C;
    if (discrim < 0.) return 0;
    float rootDiscrim = sqrtf(discrim);

    // Compute quadratic _t_ values
    float q;
    if (B < 0) q = -.5f * (B - rootDiscrim);
    else       q = -.5f * (B + rootDiscrim);
    *t0 = q / A;
    *t1 = C / q;
    if (*t0 > *t1)
    {
    	A = *t0;
    	*t0 = *t1;
    	*t1 = A;
    }
    return 1;
}

int sign(int x) {
    return (x > 0) - (x < 0);
}

int				hit_cylinder(const t_ray ray, const t_cylinder cylinder, double *t)
{//d -> ray.dir, V -> cylinder->dir, x -> ray.start
	const t_vec3	rayOrg = vec3_sub(cylinder.origin, ray.start);	// ray in space of the sphere
	t_vec3		d = vec3_sub(cylinder.origin, rayOrg);
	double		a = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
	double		b = ray.dir.x * d.x + ray.dir.z * d.z;
	double		c = d.x * d.x + d.z * d.z - cylinder.r * cylinder.r;
	double		tmp;

	tmp = b * b - a * c;
	if (tmp > 0.0)
	{
		tmp = (-b - sqrt(tmp) * sign(cylinder.r)) / a;
		// printf("Tmp: %f\n", tmp);
		if (tmp > 0.0 && tmp < *t)
		{
			*t = tmp;
			return (1);
		}
	}
	return (0);

	// float		dv = vec3_dot(ray.dir, cylinder.dir);
	// float		xv = vec3_dot(ray.start, cylinder.dir);
	// float		a = vec3_dot(ray.dir, cylinder.dir) - dv * dv;
	// float		b = vec3_dot(cylinder.dir, ray.start) - dv * xv; // /2 ?
	// float		c = vec3_dot(ray.start, ray.start) - xv * xv - cylinder.r * cylinder.r;

	// return (0);
	// (void)a;
	// (void)b;
	// (void)c;
	// float t0, t1;
	// float delta;
	// delta = b * b - 2 * a * c;

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

int				cylinder_normal(t_data *data)
{
	const t_cylinder	cylinder = data->scene.cylinders[data->closest[1]];
	const t_ray			ray = data->viewray;
	t_vec3				intersect;

	intersect = vec3_add(ray.start, vec3_mult(ray.dir, data->t));
	data->normal = vec3_norm(vec3_sub(intersect, cylinder.origin));
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
