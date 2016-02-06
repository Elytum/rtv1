#ifndef FORMS_H
# define FORMS_H

typedef struct	s_plane
{
	float		x;
	float		y;
	float		z;
}				t_plane;

typedef struct	s_sphere
{
	float		x;
	float		y;
	float		z;
	float		r;
}				t_sphere;

typedef struct	s_cylinder
{
	float		x1;
	float		y1;
	float		z1;
	float		x2;
	float		y2;
	float		z2;
	float		r;
}				t_cylinder;

typedef struct	s_cone
{
	float		x1;
	float		y1;
	float		z1;
	float		r1;
	float		x2;
	float		y2;
	float		z2;
	float		r2;
}				t_cone;

#define PLANES_INTRO "Planes:\n"
#define SPHERES_INTRO "Spheres:\n"
#define CYLINDERS_INTRO "Cylinders:\n"
#define CONES_INTRO "Cones:\n"

#endif
