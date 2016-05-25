/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forms.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 22:38:26 by achazal           #+#    #+#             */
/*   Updated: 2016/03/08 22:38:32 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORMS_H
# define FORMS_H

# define MATERIALS_INTRO "Materials:\n"
# define LIGHTS_INTRO "Lights:\n"
# define PLANES_INTRO "Planes:\n"
# define SPHERES_INTRO "Spheres:\n"
# define CYLINDERS_INTRO "Cylinders:\n"
# define CONES_INTRO "Cones:\n"

# include <vec3.h>
# include <cone.h>
# include <cylinder.h>
# include <plane.h>
# include <sphere.h>

typedef struct	s_light
{
	t_vec3		pos;
	float		r;
	float		g;
	float		b;
}				t_light;

typedef enum	e_form
{
	PLANE = 0,
	SPHERE,
	CYLINDER,
	CYLINDER_FINITE,
	CONE
}				t_form;

#endif
