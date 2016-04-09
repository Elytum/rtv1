#include <math.h>
#include <forms.h>
//https://github.com/mmp/pbrt-v2/blob/master/src/shapes/cylinder_finite.cpp
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

int				hit_cylinder_finite(const t_ray ray, const t_cylinder_finite cylinder_finite, double *t)
{//d -> ray.dir, V -> cylinder_finite->dir, x -> ray.start

//sa -> ray.start sb -> ray.dir
//p -> cylinder_finite.q q -> cylinder_finite.p r -> cylinder_finite.r
	t_vec3	d = vec3_sub(cylinder_finite.p, cylinder_finite.q);
	t_vec3	m = vec3_sub(ray.start, cylinder_finite.q);
	t_vec3	n = vec3_sub(ray.dir, ray.start);
	double 	md = vec3_dot(m, d);
	double 	nd = vec3_dot(n, d);
	double 	dd = vec3_dot(d, d);

	if (md < 0.0f && md + nd < 0.0f)
		return (0);
	if (md > dd && md + nd > dd)
		return (0);
	double	nn = vec3_dot(n, n);
	double	mn = vec3_dot(m, n);
	double 	a = dd * nn - nd * nd;
	double 	k = vec3_dot(m, m) - cylinder_finite.r * cylinder_finite.r;
	double 	c = dd * k - md * md;
	if (ABS(a) < EPSILON)
	{
		if (c > 0.0f)
			return (0);
		if (md < 0.0f)
			*t = -mn / nn;
		else if (md > dd)
			*t = (nd - mn) / nn;
		else
			*t = 0.0f;
		return (1);
	}
	double b = dd * mn - nd * md;
	double discr = b * b - a * c;
	if (discr < 0.0f)
		return (0);
	double tmp = (-b - sqrt(discr)) / a;
	if (tmp < 0.0f || tmp > 1.0f)
		return (0);
	if (md + tmp * nd < 0.0f)
	{
		if (nd <= 0.0f)
			return (0);
		tmp = -md / nd;
		if (k + 2 * tmp * (mn + tmp * nn) > 0.0f)
			return (0);
		else
		{
			*t = tmp;
			return (1);
		}
	}
	else if (md + tmp * nd > dd)
	{
		if (nd >= 0.0f)
			return (0);
		tmp = (dd - md) / nd;
		if (k + dd - 2 * md + tmp * (2 * (md - nd) + tmp * nn) > 0.0f)
			return (0);
		else
		{
			*t = tmp;
			return (1);
		}
	}
	*t = tmp;
	return (1);
	// const t_vec3	rayOrg = vec3_sub(cylinder_finite.q, ray.start);	// ray in space of the sphere
	// t_vec3		d = vec3_sub(cylinder_finite.q, rayOrg);
	// double		a = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;//vec3_dot(ray.dir, ray.dir);
	// double		b = ray.dir.x * d.x + ray.dir.z * d.z;
	// double		c = d.x * d.x + d.z * d.z - cylinder_finite.r * cylinder_finite.r;
	// double		tmp;

	// tmp = b * b - a * c;
	// if (tmp > 0.0)
	// {
	// 	tmp = (-b - sqrt(tmp) * sign(cylinder_finite.r)) / a;
	// 	// printf("Tmp: %f\n", tmp);
	// 	if (tmp > 0.0 && tmp < *t)
	// 	{
	// 		*t = tmp;
	// 		return (1);
	// 	}
	// }
	// return (0);

	// double		dv = vec3_dot(ray.dir, cylinder_finite.p);
	// double		xv = vec3_dot(ray.start, cylinder_finite.p);
	// double		a = vec3_dot(ray.dir, cylinder_finite.p) - dv * dv;
	// double		b = vec3_dot(cylinder_finite.p, ray.start) - dv * xv; // /2 ?
	// double		c = vec3_dot(ray.start, ray.start) - xv * xv - cylinder_finite.r * cylinder_finite.r;

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

int				cylinder_finite_normal(t_data *data)
{
	const t_cylinder_finite	cylinder_finite = data->scene.cylinders_finite[data->closest[1]];
	const t_ray			ray = data->viewray;
	t_vec3				intersect;

	intersect = vec3_add(ray.start, vec3_mult(ray.dir, data->t));
	data->normal = vec3_norm(vec3_sub(intersect, cylinder_finite.q));
	data->material = data->scene.materials[data->scene.cylinders_finite[data->closest[1]].m];
	data->new_start = vec3_add(data->viewray.start, vec3_mult(data->viewray.dir, data->t));
	return 1;
}

void			find_closest_cylinder_finite(t_data *data, const t_ray ray, double *t)
{
	unsigned int			i;

	i = 0;
	while (i < data->scene.cylinders_finite_nb)
	{
		if (hit_cylinder_finite(ray, data->scene.cylinders_finite[i], t))
		{
			data->closest[0] = CYLINDER_FINITE;
			data->closest[1] = i;
		}
		++i;
	}
}

int				hit_any_cylinder_finite(t_data *data, const t_ray ray, double t)
{
	unsigned int			i;

	i = 0;
	while (i < data->scene.cylinders_finite_nb)
	{
		if (hit_cylinder_finite(ray, data->scene.cylinders_finite[i], &t))
			return (1);
		++i;
	}
	return (0);
}
