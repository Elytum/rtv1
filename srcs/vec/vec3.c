#include <vec3.h>
#include <stdio.h>
#include <math.h>

t_vec3			vec3_new(const double x, const double y, const double z)
{
	t_vec3		ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_vec3			vec3_reverse(const t_vec3 vec)
{
	t_vec3		ret;

	ret.x = -vec.x;
	ret.y = -vec.y;
	ret.z = -vec.z;
	return (ret);
}

t_vec3			vec3_add(const t_vec3 vec1, const t_vec3 vec2)
{
	t_vec3		ret;

	ret.x = vec1.x + vec2.x;
	ret.y = vec1.y + vec2.y;
	ret.z = vec1.z + vec2.z;
	return (ret);
}

t_vec3			vec3_sub(const t_vec3 vec1, const t_vec3 vec2)
{
	t_vec3		ret;

	ret.x = vec1.x - vec2.x;
	ret.y = vec1.y - vec2.y;
	ret.z = vec1.z - vec2.z;
	return (ret);
}

t_vec3			vec3_mult(const t_vec3 vec, const double m)
{
	t_vec3		ret;

	ret.x = vec.x * m;
	ret.y = vec.y * m;
	ret.z = vec.z * m;
	return (ret);
}

double			vec3_dot(const t_vec3 vec1, const t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vec3			vec3_cross(const t_vec3 vec1, const t_vec3 vec2)
{
	t_vec3		ret;

	ret.x = vec1.x * vec2.x;
	ret.y = vec1.y * vec2.y;
	ret.z = vec1.z * vec2.z;
	return (ret);
}

double				vec3_len(const t_vec3 vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vec3				vec3_norm(const t_vec3 vec)
{
	const double	len = vec3_len(vec);
	t_vec3			ret;

	ret.x = vec.x / len;
	ret.y = vec.y / len;
	ret.z = vec.z / len;
	return (ret);
}

t_vec3				vec3_rotx(const t_vec3 vec, const double r)
{
	double			cos_r;
	double			sin_r;
	t_vec3			ret;

	if (!r)
		return (vec);
	cos_r = cos(r);
	sin_r = sin(r);
	ret.x = vec.x;
	ret.y = cos_r * vec.y - sin_r * vec.z;
	ret.z = sin_r * vec.y + cos_r * vec.z;
	return (ret);
}

t_vec3				vec3_roty(const t_vec3 vec, const double r)
{
	double			cos_r;
	double			sin_r;
	t_vec3			ret;

	if (!r)
		return (vec);
	cos_r = cos(r);
	sin_r = sin(r);
	ret.x = sin_r * vec.z + cos_r * vec.x;
	ret.y = vec.y;
	ret.z = cos_r * vec.z - sin_r * vec.x;
	return (ret);
}

t_vec3				vec3_rotz(const t_vec3 vec, const double r)
{
	double			cos_r;
	double			sin_r;
	t_vec3			ret;

	if (!r)
		return (vec);
	cos_r = cos(r);
	sin_r = sin(r);
	ret.x = cos_r * vec.x - sin_r * vec.y;
	ret.y = sin_r * vec.x + cos_r * vec.y;;
	ret.z = vec.z;
	return (ret);
}

void			vec3_describe(const t_vec3 vec)
{
	dprintf(1, "(%f %f %f)", vec.x, vec.y, vec.z);
}