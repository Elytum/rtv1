#ifndef FORMS_H
# define FORMS_H

#include <vec3.h>

typedef struct	s_material
{
	float		r;
	float		g;
	float		b;
	float		c;
}				t_material;

typedef struct	s_light
{
	t_vec3		pos;
	float		r;
	float		g;
	float		b;
}				t_light;

typedef struct	s_plane
{
	float		x;
	float		y;
	float		z;
	int			m;
}				t_plane;

typedef struct	s_sphere
{
	// float		x;
	// float		y;
	// float		z;
	t_vec3		center;
	float		r;
	int			m;
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
	int			m;
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
	int			m;
}				t_cone;

typedef enum	s_form
{
	PLAN = 0,
	SPHERE,
	CYLINDER,
	CONE
}				t_form;

#define MATERIALS_INTRO "Materials:\n"
#define LIGHTS_INTRO "Lights:\n"
#define PLANES_INTRO "Planes:\n"
#define SPHERES_INTRO "Spheres:\n"
#define CYLINDERS_INTRO "Cylinders:\n"
#define CONES_INTRO "Cones:\n"

#include <cone.h>
#include <cylinder.h>
#include <plane.h>
#include <sphere.h>

#endif
