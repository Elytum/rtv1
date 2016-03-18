#include <math.h>
#include <forms.h>

int				hit_plane(const t_ray ray, const t_plane plane, float *t)
{
	const	float d = vec3_dot(normal, coord);

	return (0);
	(void)ray;
	(void)plane;
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

// bool linePlaneIntersection(Vector& contact, Vector ray, Vector rayOrigin, 
//                            Vector normal, Vector coord) {
//     // get d value
//     float d = Dot(normal, coord);

//     if (Dot(normal, ray) == 0) {
//         return false; // No intersection, the line is parallel to the plane
//     }

//     // Compute the X value for the directed line ray intersecting the plane
//     float x = (d - Dot(normal, rayOrigin)) / Dot(normal, ray);

//     // output contact point
//     *contact = rayOrigin + normalize(ray)*x; //Make sure your ray vector is normalized
//     return true;
// }

void			find_closest_plane(t_scene scene, const t_ray ray, int *closest, float *t)
{
	unsigned int			i;

	i = 0;
	while (i < scene.planes_nb)
	{
		if (hit_plane(ray, scene.planes[i], t))
		{
			closest[0] = PLANE;
			closest[1] = i;
		}
		++i;
	}
}