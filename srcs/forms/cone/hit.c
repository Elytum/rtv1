#include <math.h>
#include <forms.h>

/*
static t_vec	*rt_cone(t_ray ray, t_cone *cone, float *distance)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float	dist1;
	float	dist2;
	float	alpha;
	t_vec	*tmp1;
	t_vec	*origin;
	t_vec	*tmp2;
	t_vec	*raydir;

	alpha = cone->angle / 180 * M_PI;
	origin = sous_vectors(ray.start, cone->pos);
	tmp1 = sous_vectors(ray.dir, mult_vector(cone->axe, dot_product(ray.dir, cone->axe)));
	tmp2 = sous_vectors(origin, mult_vector(cone->axe, dot_product(origin, cone->axe)));
	a = (pow(cos(alpha), 2) * dot_product(tmp1, tmp1)) - (pow(sin(alpha), 2) * carre(dot_product(ray.dir, cone->axe)));
	b = 2 * (pow(cos(alpha), 2) * dot_product(tmp1, tmp2)) - 2 * (pow(sin(alpha), 2) * dot_product(ray.dir, cone->axe) * dot_product(origin, cone->axe));
	c = (pow(cos(alpha), 2) * dot_product(tmp2, tmp2)) - (pow(sin(alpha), 2) * carre(dot_product(origin, cone->axe)));
	if ((delta = carre(b) - (4 * a * c)) < 0)
		return (0);
	else
	{
		dist1 = (b * -1 + sqrt(delta)) / (2 * a);
		dist2 = (b * -1 - sqrt(delta)) / (2 * a);
		if (dist1 < 0.0 && dist2 < 0.0)
			return (0);
		else if (dist1 >= 0 && dist2 >= 0)
			dist1 = dist2;
		if (dist1 >= 0.0 && dist1 < *distance)
		{
			*distance = dist1;
			raydir = add_vectors(ray.start, mult_vector(ray.dir, *distance));
			return (sous_vectors(raydir, cone->pos));
		}
	}
	return (NULL);
}
*/
int				hit_cone(const t_ray ray, const t_cone cone, double *t)
{
	double			a;
	double			b;
	double			c;
	double			delta;
	double			alpha;
	t_vec3			tmp1;
	t_vec3			origin;
	t_vec3			tmp2;

	alpha = cone.angle / 180 * M_PI;
	origin = vec3_sub(ray.start, cone.origin);
	tmp1 = vec3_sub(ray.dir, vec3_mult(cone.dir, vec3_dot(ray.dir, cone.dir)));
	tmp2 = vec3_sub(origin, vec3_mult(cone.dir, vec3_dot(origin, cone.dir)));
	a = pow(cos(alpha), 2) * vec3_dot(tmp1, tmp1) - pow(sin(alpha), 2) * pow(vec3_dot(ray.dir, cone.dir), 2);
	b = 2 * (pow(cos(alpha), 2) * vec3_dot(tmp1, tmp2)) - 2 * (pow(sin(alpha), 2) * vec3_dot(ray.dir, cone.dir) * vec3_dot(origin, cone.dir));
	c = pow(cos(alpha), 2) * vec3_dot(tmp2, tmp2) - pow(sin(alpha), 2) * pow(vec3_dot(origin, cone.dir), 2);

	delta = b * b - 4 * a * c;

	if (delta < 0)
		return (0);
	else if (delta == 0)
	{
		if (*t > b && b > 0.1)
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
		if (*t > x0 && x0 > 0.1)
		{
			*t = x0;
			return (1);
		}
	}
	return (0);
}

int				cone_normal(t_data *data)
{
	const t_cone		cone = data->scene.cones[data->closest[1]];
	const t_ray			ray = data->viewray;
	t_vec3				intersect;

	intersect = vec3_add(ray.start, vec3_mult(ray.dir, data->t));
	data->normal = vec3_norm(vec3_sub(intersect, cone.origin));
	data->material = data->scene.materials[data->scene.cones[data->closest[1]].m];
	data->new_start = vec3_add(data->viewray.start, vec3_mult(data->viewray.dir, data->t));
	return 1;
	(void)data;
}

void			find_closest_cone(t_data *data, const t_ray ray, double *t)
{
	unsigned int			i;

	i = 0;
	while (i < data->scene.cones_nb)
	{
		// dprintf(1, "Calling\n");
		if (hit_cone(ray, data->scene.cones[i], t))
		{
			data->closest[0] = CONE;
			data->closest[1] = i;
		}
		// dprintf(1, "Called\n");
		++i;
	}
}

int				hit_any_cone(t_data *data, const t_ray ray, double t)
{
	unsigned int			i;

	i = 0;
	while (i < data->scene.cones_nb)
	{
		if (hit_cone(ray, data->scene.cones[i], &t))
			return (1);
		++i;
	}
	return (0);
}

// #include <math.h>
// #include <forms.h>
// #include <ray.h>
	
// int				hit_cylinder(const t_ray ray, const t_cylinder cylinder, double *t)
// {
// 	float			a;
// 	float			b;
// 	float			c;
// 	float			delta;
// 	float			dist1;
// 	float			dist2;
// 	t_vec3			tmp1;
// 	t_vec3			origin;
// 	t_vec3			tmp2;

// 	origin = vec3_sub(ray.start, cylinder.origin);
// 	tmp1 = vec3_sub(ray.dir, vec3_mult(cylinder.dir, vec3_dot(ray.dir, cylinder.dir)));
// 	tmp2 = vec3_sub(origin, vec3_mult(cylinder.dir, vec3_dot(origin, cylinder.dir)));
// 	a = vec3_dot(tmp1, tmp1);
// 	b = 2 * vec3_dot(tmp1, tmp2);
// 	c = vec3_dot(tmp2, tmp2) - cylinder.r * cylinder.r;
// 	if ((delta = b * b - (4 * a * c)) < 0)
// 		return (0);
// 	else
// 	{
// 		dist1 = (b * -1.0 + sqrt(delta)) / (2.0 * a);
// 		dist2 = (b * -1.0 - sqrt(delta)) / (2.0 * a);
// 		if (dist1 < 0.1 && dist2 < 0.1)
// 			return (0);
// 		else if (dist1 >= 0.1 && dist2 >= 0.1)
// 			dist1 = dist2;
// 		if (dist1 >= 0.1 && dist1 < *t)
// 		{
// 			*t = dist1;
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

// int				cylinder_normal(t_data *data)
// {
// 	const t_cylinder	cylinder = data->scene.cylinders[data->closest[1]];
// 	const t_ray			ray = data->viewray;
// 	t_vec3				intersect;

// 	intersect = vec3_add(ray.start, vec3_mult(ray.dir, data->t));
// 	data->normal = vec3_norm(vec3_sub(vec3_new(intersect.x, 0, intersect.z), vec3_new(cylinder.origin.x, 0, cylinder.origin.z)));
// 	data->material = data->scene.materials[data->scene.cylinders[data->closest[1]].m];
// 	data->new_start = vec3_add(data->viewray.start, vec3_mult(data->viewray.dir, data->t));
// 	return 1;
// }

// void			find_closest_cylinder(t_data *data, const t_ray ray, double *t)
// {
// 	unsigned int			i;

// 	i = 0;
// 	while (i < data->scene.cylinders_nb)
// 	{
// 		if (hit_cylinder(ray, data->scene.cylinders[i], t))
// 		{
// 			data->closest[0] = CYLINDER;
// 			data->closest[1] = i;
// 		}
// 		++i;
// 	}
// }

// int				hit_any_cylinder(t_data *data, const t_ray ray, double t)
// {
// 	unsigned int			i;

// 	i = 0;
// 	while (i < data->scene.cylinders_nb)
// 	{
// 		if (hit_cylinder(ray, data->scene.cylinders[i], &t))
// 			return (1);
// 		++i;
// 	}
// 	return (0);
// }
