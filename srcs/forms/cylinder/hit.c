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

// static float	vec3_dot_x(const t_vec3 v1, const t_vec3 v2)
// {
// 	return (v1.y * v2.y + v1.z * v2.z);
// }

// static float	vec3_dot_y(const t_vec3 v1, const t_vec3 v2)
// {
// 	return (v1.x * v2.x + v1.z * v2.z);
// }

// static float	vec3_dot_z(const t_vec3 v1, const t_vec3 v2)
// {
// 	return (v1.x * v2.x + v1.y * v2.y);
// }

// static int		hit_x(const t_ray ray, const t_cylinder cylinder, double *t)
// {
// 	// const t_vec3	rayOrg = vec3_sub(ray.start, cylinder.origin);	// ray in space of the sphere
// 	// t_vec3		d = vec3_sub(cylinder.origin, rayOrg);
// 	// double		a = vec3_dot_x(ray.dir, ray.dir);//ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z; //dotx
// 	// double		b = vec3_dot_x(ray.dir, d);//ray.dir.x * d.x + ray.dir.z * d.z;
// 	// double		c = vec3_dot_x(d, d) - cylinder.r * cylinder.r; //dotx
// 	// // double		c = ft_dotx(sphere->c, sphere->c) + ft_dotx(rayorg, rayorg) - (2.0 * ft_dotx(rayorg, sphere->c)) - (sphere->r2);
// 	// double		delta;

// 	// delta = b * b - a * c;
// 	// if (delta >= 0.0f)
// 	// {
// 	// 	double t0, t1;
// 	// 	t0 = (-b - sqrt(delta)) / a;
// 	// 	t1 = (-b + sqrt(delta)) / a;
// 	// 	if (t0 > t1)
// 	// 		delta = t0;
// 	// 	else
// 	// 		delta = t1;
// 	// 	if (delta >= 0.0f && delta < *t)
// 	// 	{
// 	// 		*t = delta;
// 	// 		return (1);
// 	// 	}
// 	// }
// 	// return (0);
// 	const t_vec3	tmp = vec3_rotx(cylinder.dir, 1);
// 	const t_vec3	rayOrg = vec3_sub(ray.start, cylinder.origin);	// ray in space of the sphere
// 	double			a = vec3_dot_x(ray.dir, ray.dir);
// 	double			b = vec3_dot_x(vec3_mult(vec3_sub(rayOrg, tmp), 2.0), ray.dir);
// 	double			c = vec3_dot_x(tmp, tmp) + vec3_dot_x(rayOrg, rayOrg) - 2 * vec3_dot_x(rayOrg, tmp) - cylinder.r * cylinder.r;
// 	double			delt = b * b - 4 * a * c;
// 	double			s;
// 	double			t0;
// 	double			t1;

// 	if (delt > 0)
// 	{
// 		s = sqrt(delt);
// 		t0 = (-b - s) / (2 * a);
// 		t1 = (-b + s) / (2 * a);
// 		if (t1 > t0)
// 			t0 = t1;
// 		if (t0 < 0)
// 			return (0);
// 		*t = t0;
// 		return (1);
// 	}
// 	return (0);
// }

// static int		hit_y(const t_ray ray, const t_cylinder cylinder, double *t)
// {
// 	// const t_vec3	rayOrg = vec3_sub(ray.start, cylinder.origin);	// ray in space of the sphere
// 	// t_vec3		d = vec3_sub(cylinder.origin, rayOrg);
// 	// double		a = vec3_dot_y(ray.dir, ray.dir);//ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z; //dotx
// 	// double		b = vec3_dot_y(ray.dir, d);//ray.dir.x * d.x + ray.dir.z * d.z;
// 	// double		c = vec3_dot_y(d, d) - cylinder.r * cylinder.r; //dotx
// 	// // double		c = ft_dotx(sphere->c, sphere->c) + ft_dotx(rayorg, rayorg) - (2.0 * ft_dotx(rayorg, sphere->c)) - (sphere->r2);
// 	// double		delta;

// 	// delta = b * b - a * c;
// 	// if (delta >= 0.0f)
// 	// {
// 	// 	double t0, t1;
// 	// 	t0 = (-b - sqrt(delta)) / a;
// 	// 	t1 = (-b + sqrt(delta)) / a;
// 	// 	if (t0 > t1)
// 	// 		delta = t0;
// 	// 	else
// 	// 		delta = t1;
// 	// 	if (delta >= 0.0f && delta < *t)
// 	// 	{
// 	// 		*t = delta;
// 	// 		return (1);
// 	// 	}
// 	// }
// 	// return (0);
// 	const t_vec3	rayOrg = vec3_sub(ray.start, cylinder.origin);	// ray in space of the sphere
// 	double			a = vec3_dot_y(ray.dir, ray.dir);
// 	double			b = vec3_dot_y(vec3_mult(vec3_sub(rayOrg, cylinder.dir), 2.0), ray.dir);
// 	double			c = vec3_dot_y(cylinder.dir, cylinder.dir) + vec3_dot_y(rayOrg, rayOrg) - 2 * vec3_dot_y(rayOrg, cylinder.dir) - cylinder.r * cylinder.r;
// 	double			delt = b * b - 4 * a * c;
// 	double			s;
// 	double			t0;
// 	double			t1;

// 	if (delt > 0)
// 	{
// 		s = sqrt(delt);
// 		t0 = (-b - s) / (2 * a);
// 		t1 = (-b + s) / (2 * a);
// 		if (t1 > t0)
// 			t0 = t1;
// 		if (t0 < 0)
// 			return (0);
// 		*t = t0;
// 		return (1);
// 	}
// 	return (0);
// }

// static int		hit_z(const t_ray ray, const t_cylinder cylinder, double *t)
// {
// 	// const t_vec3	rayOrg = vec3_sub(ray.start, cylinder.origin);	// ray in space of the sphere
// 	// t_vec3		d = vec3_sub(cylinder.origin, rayOrg);
// 	// double		a = vec3_dot_z(ray.dir, ray.dir);//ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z; //dotx
// 	// double		b = vec3_dot_z(ray.dir, d);//ray.dir.x * d.x + ray.dir.z * d.z;
// 	// double		c = vec3_dot_z(d, d) - cylinder.r * cylinder.r; //dotx
// 	// // double		c = ft_dotx(sphere->c, sphere->c) + ft_dotx(rayorg, rayorg) - (2.0 * ft_dotx(rayorg, sphere->c)) - (sphere->r2);
// 	// double		delta;

// 	// delta = b * b - a * c;
// 	// if (delta >= 0.0f)
// 	// {
// 	// 	double t0, t1;
// 	// 	t0 = (-b - sqrt(delta)) / a;
// 	// 	t1 = (-b + sqrt(delta)) / a;
// 	// 	if (t0 > t1)
// 	// 		delta = t0;
// 	// 	else
// 	// 		delta = t1;
// 	// 	if (delta >= 0.0f && delta < *t)
// 	// 	{
// 	// 		*t = delta;
// 	// 		return (1);
// 	// 	}
// 	// }
// 	// return (0);
// 	const t_vec3	rayOrg = vec3_sub(ray.start, cylinder.origin);	// ray in space of the sphere
// 	double			a = vec3_dot_z(ray.dir, ray.dir);
// 	double			b = vec3_dot_z(vec3_mult(vec3_sub(rayOrg, cylinder.dir), 2.0), ray.dir);
// 	double			c = vec3_dot_z(cylinder.dir, cylinder.dir) + vec3_dot_z(rayOrg, rayOrg) - 2 * vec3_dot_z(rayOrg, cylinder.dir) - cylinder.r * cylinder.r;
// 	double			delt = b * b - 4 * a * c;
// 	double			s;
// 	double			t0;
// 	double			t1;

// 	if (delt >= 0)
// 	{
// 		s = sqrt(delt);
// 		t0 = (-b - s) / (2 * a);
// 		t1 = (-b + s) / (2 * a);
// 		if (t1 > t0)
// 			t0 = t1;
// 		if (t0 <= 0)
// 			return (0);
// 		*t = t0;
// 		return (1);
// 	}
// 	return (0);
// }
// vector -> ray.dir
// eye -> rayOrg
// R -> form.r

void		moved_ray(t_ray ray, t_obj *tmp, int invert)
{
	// if (invert == 1)
	// {
	// 	all_rot(eye, &tmp->rot, invert);
	// 	all_rot(vector, &tmp->rot, invert);
	// }

	t_ray	moved;

	eye->x += invert * tmp->pos.x;
	eye->y += invert * tmp->pos.y;
	eye->z += invert * tmp->pos.z;
	vector->x += invert * tmp->pos.x;
	vector->y += invert * tmp->pos.y;
	vector->z += invert * tmp->pos.z;

	all_rot(eye, &tmp->rot, invert);
	all_rot(vector, &tmp->rot, invert);

	// if (invert == -1)
	// {
	// 	all_rot(eye, &tmp->rot, invert);
	// 	all_rot(vector, &tmp->rot, invert);
	// }
}

int				hit_cylinder(const t_ray ray, const t_cylinder cylinder, double *t)
{//d -> ray.dir, V -> cylinder->dir, x -> ray.start
	// double	a;// a = pow(vector->x, 2) + pow(vector->y, 2) + pow(vector->z, 2);
	// double	b;// b = 2 * (eye->x * vector->x + eye->y * vector->y + eye->z * vector->z);
	// double	c;// c = pow(eye->x, 2) + pow(eye->y, 2) + pow(eye->z, 2) - pow(R, 2);
// double	a;
// double	b;
// double	c;
// double	delta;

// a = pow(vector->x, 2) + pow(vector->y, 2);
// b = 2 * (eye->x * vector->x + eye->y * vector->y);
// c = pow(eye->x, 2) + pow(eye->y, 2) - pow(R / 1.5, 2);
// delta = pow(b, 2) - 4 * a * c;
// k[0] = (delta >= 0 ? (-b - sqrt(delta)) / (2 * a) : -1);
// k[1] = (delta >= 0 ? (-b + sqrt(delta)) / (2 * a) : -1);

	t_ray	moved_ray = move_eye(ray, obj, -1);

	double	a;
	double	b;
	double	c;
	double	delta;
	const t_vec3	rayOrg = vec3_sub(cylinder.origin, ray.start);	// ray in space of the sphere

	// // a = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y + ray.dir.z * ray.dir.z;
	// a = vec3_dot(ray.dir, ray.dir);
	// b = 2 * vec3_dot(ray.dir, rayOrg);
	// // b = 2 * (rayOrg.x * ray.dir.x + rayOrg.y * ray.dir.y + rayOrg.z * ray.dir.z);
	// // c = rayOrg.x * rayOrg.x + rayOrg.y * rayOrg.y + rayOrg.z * rayOrg.z - sphere.r * sphere.r;
	// c = vec3_dot(rayOrg, rayOrg) - sphere.r * sphere.r;
	// // delta = b * b - 4 * a * c;
	// delta = b * b - 4 * a * c;
	// if (delta < 0)
	// 	return (0);

	a = vec3_dot(ray.dir, ray.dir);
	// b = 2 * vec3_dot(ray.dir, rayOrg);
	b = 2 * (rayOrg.x * ray.dir.x + rayOrg.y * ray.dir.y);
	// c = vec3_dot(rayOrg, rayOrg) - cylinder.r / 1.5 * cylinder.r / 1.5;
	c = rayOrg.x * rayOrg.x + rayOrg.y * rayOrg.y - (cylinder.r / 1.5) * (cylinder.r / 1.5);

	delta = b * b - 4 * a * c;
	printf("delta: %f\n", delta);
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
		c = (-b - delta) / 2 * a;
		delta = (-b + delta) / 2 * a;
		printf("%f %f\n", c, delta);
		if (c >= 0 || delta >= 0)
		{
			*t = (c > delta) ? c : delta;
			return (1);
		}
	}
	return (0);











	(void)ray;
	(void)cylinder;
	(void)t;
	return (0);
	// double d = ray.dir.z 


	// double	a = (ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y);
	// double	b = 2 * (cylinder.origin.x + cylinder.origin.y);
	// double	c = cylinder.origin.x * cylinder.origin.x + cylinder.origin.y * cylinder.origin.y - cylinder.r * cylinder.r;
	// double	delta = b * b - 4 * a * c;

	// // if (delta < 0)
	// // 	return (0);

	// double			t0;
	// double			t1;
	// if (delta < 0.0f)
	// 	return 0; // pas d'intersection
	// if (delta != 0)
	// {
	// 	delta = sqrt(delta);
	// 	t0 = (b + delta) / a;
	// 	t1 = (b - delta) / a;
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

	// // printf("%f\n", delta);
	// // return (0);
	// // *t = 1;
	// return (1);


	// if (cylinder.dir.x && hit_x(ray, cylinder, t))
	// 	return (1);
	// if (cylinder.dir.y && hit_y(ray, cylinder, t))
	// 	return (1);
	// if (cylinder.dir.z && hit_z(ray, cylinder, t))
	// 	return (1);
	// return (0);

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
