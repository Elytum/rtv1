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
	t_vec3		normal;
	t_vec3		coord;
	int			m;
}				t_plane;

typedef struct	s_sphere
{
	t_vec3		center;
	double		r;
	int			m;
}				t_sphere;

typedef struct	s_cylinder
{
	t_vec3		origin;
	t_vec3		dir;
	float		r;
	int			m;
}				t_cylinder;

typedef struct	s_cylinder_finite
{
	t_vec3		p;
	t_vec3		q;
	float		r;
	int			m;
}				t_cylinder_finite;

typedef struct	s_cone
{
	t_vec3		origin;
	t_vec3		dir;
	float		angle;
	int			m;
}				t_cone;

typedef enum	s_form
{
	PLANE = 0,
	SPHERE,
	CYLINDER,
	CYLINDER_FINITE,
	CONE
}				t_form;

#define MATERIALS_INTRO "Materials:\n"
#define LIGHTS_INTRO "Lights:\n"
#define PLANES_INTRO "Planes:\n"
#define SPHERES_INTRO "Spheres:\n"
#define CYLINDERS_INTRO "Cylinders:\n"
#define CYLINDERS_FINITE_INTRO "Cylinders finite:\n"
#define CONES_INTRO "Cones:\n"

#include <cone.h>
#include <cylinder.h>
#include <plane.h>
#include <sphere.h>
#include <cylinder_finite.h>

#endif
