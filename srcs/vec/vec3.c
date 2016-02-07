#include <vec3.h>
#include <stdio.h>

t_vec3			vec3_new(const float x, const float y, const float z)
{
	t_vec3		ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
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

t_vec3			vec3_mult(const t_vec3 vec, const float m)
{
	t_vec3		ret;

	ret.x = vec.x * m;
	ret.y = vec.y * m;
	ret.z = vec.z * m;
	return (ret);
}

float			vec3_dot(const t_vec3 vec1, const t_vec3 vec2)
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

void			vec3_describe(const t_vec3 vec)
{
	dprintf(1, "(%f %f %f)", vec.x, vec.y, vec.z);
}