#ifndef VEC3_H
# define VEC3_H

typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

t_vec3			vec3_new(const float x, const float y, const float z);
t_vec3			vec3_add(const t_vec3 vec1, const t_vec3 vec2);
t_vec3			vec3_sub(const t_vec3 vec1, const t_vec3 vec2);
t_vec3			vec3_mult(const t_vec3 vec, const float m);
float			vec3_dot(const t_vec3 vec1, const t_vec3 vec2);
void			vec3_describe(const t_vec3 vec);

#endif
