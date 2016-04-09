#include <math.h>
#include <forms.h>
//https://github.com/mmp/pbrt-v2/blob/master/src/shapes/cylinder.cpp
#define ABS(x)  ( ( (x) < 0) ? -(x) : (x) )
#define EPSILON 1.19209290e-07F

// char	Quadratic(double A, double B, double C, double *t0, double *t1) {
//     // Find quadratic discriminant
//     double discrim = B * B - 4.f * A * C;
//     if (discrim < 0.) return 0;
//     double rootDiscrim = sqrtf(discrim);

//     // Compute quadratic _t_ values
//     double q;
//     if (B < 0) q = -.5f * (B - rootDiscrim);
//     else       q = -.5f * (B + rootDiscrim);
//     *t0 = q / A;
//     *t1 = C / q;
//     if (*t0 > *t1)
//     {
//     	A = *t0;
//     	*t0 = *t1;
//     	*t1 = A;
//     }
//     return 1;
// }

// int sign(int x) {
//     return (x > 0) - (x < 0);
// }

static float	dot_x(const t_vec3 v1, const t_vec3 v2)
{
	return (v1.x * v2.x + v1.z * v2.z);
}

static int		hit_x(const t_ray ray, const t_cylinder cylinder, double *t)
{
	const t_vec3	rayOrg = vec3_sub(cylinder.origin, ray.start);	// ray in space of the sphere
	t_vec3		d = vec3_sub(cylinder.origin, rayOrg);
	double		a = dot_x(ray.dir, ray.dir);//ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z; //dotx
	double		b = dot_x(ray.dir, d);//ray.dir.x * d.x + ray.dir.z * d.z;
	double		c = dot_x(d, d) - cylinder.r * cylinder.r; //dotx
	// double		c = ft_dotx(sphere->c, sphere->c) + ft_dotx(rayorg, rayorg) - (2.0 * ft_dotx(rayorg, sphere->c)) - (sphere->r2);
	double		delta;

	delta = b * b - a * c;
	if (delta >= 0.0f)
	{
		double t0, t1;
		t0 = (-b - sqrt(delta)) / a;
		t1 = (-b + sqrt(delta)) / a;
		if (t0 > t1)
			delta = t0;
		else
			delta = t1;
		if (delta >= 0.0f && delta < *t)
		{
			*t = delta;
			return (1);
		}
	}
	return (0);
}

int				hit_cylinder(const t_ray ray, const t_cylinder cylinder, double *t)
{//d -> ray.dir, V -> cylinder->dir, x -> ray.start
	if (hit_x(ray, cylinder, t))
		return (1);
	return (0);

//sa -> ray.start sb -> ray.dir
//p -> cylinder.origin q -> cylinder.dir r -> cylinder.r
	// t_vec3	d = vec3_sub(cylinder.dir, cylinder.origin);
	// t_vec3	m = vec3_sub(ray.start, cylinder.origin);
	// t_vec3	n = vec3_sub(ray.dir, ray.start);
	// double 	md = vec3_dot(m, d);
	// double 	nd = vec3_dot(n, d);
	// double 	dd = vec3_dot(d, d);

	// if (md < 0.0f && md + nd < 0.0f)
	// 	return (0);
	// if (md > dd && md + nd > dd)
	// 	return (0);
	// double	nn = vec3_dot(n, n);
	// double	mn = vec3_dot(m, n);
	// double 	a = dd * nn - nd * nd;
	// double 	k = vec3_dot(m, m) - cylinder.r * cylinder.r;
	// double 	c = dd * k - md * md;
	// if (ABS(a) < EPSILON)
	// {
	// 	if (c > 0.0f)
	// 		return (0);
	// 	if (md < 0.0f)
	// 		*t = -mn / nn;
	// 	else if (md > dd)
	// 		*t = (nd - mn) / nn;
	// 	else
	// 		*t = 0.0f;
	// 	return (1);
	// }
	// double b = dd * mn - nd * md;
	// double discr = b * b - a * c;
	// if (discr < 0.0f)
	// 	return (0);
	// double tmp = (-b - sqrt(discr)) / a;
	// if (tmp < 0.0f || tmp > 1.0f)
	// 	return (0);
	// if (md + tmp * nd < 0.0f)
	// {
	// 	if (nd <= 0.0f)
	// 		return (0);
	// 	tmp = -md / nd;
	// 	if (k + 2 * tmp * (mn + tmp * nn) > 0.0f)
	// 		return (0);
	// 	else
	// 	{
	// 		*t = tmp;
	// 		return (1);
	// 	}
	// }
	// else if (md + tmp * nd > dd)
	// {
	// 	if (nd >= 0.0f)
	// 		return (0);
	// 	tmp = (dd - md) / nd;
	// 	if (k + dd - 2 * md + tmp * (2 * (md - nd) + tmp * nn) > 0.0f)
	// 		return (0);
	// 	else
	// 	{
	// 		*t = tmp;
	// 		return (1);
	// 	}
	// }
	// *t = tmp;
	// return (1);



	

	// double		dv = vec3_dot(ray.dir, cylinder.dir);
	// double		xv = vec3_dot(ray.start, cylinder.dir);
	// double		a = vec3_dot(ray.dir, cylinder.dir) - dv * dv;
	// double		b = vec3_dot(cylinder.dir, ray.start) - dv * xv; // /2 ?
	// double		c = vec3_dot(ray.start, ray.start) - xv * xv - cylinder.r * cylinder.r;

	// return (0);
	// (void)a;
	// (void)b;
	// (void)c;
	// double t0, t1;
	// double delta;
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
