/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 22:38:26 by achazal           #+#    #+#             */
/*   Updated: 2016/03/08 22:38:32 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include <raytracer.h>
# include <ray.h>

typedef struct s_data	t_data;

typedef struct			s_cylinder
{
	t_vec3				origin;
	t_vec3				dir;
	float				r;
	int					m;
}						t_cylinder;

int						hit_cylinder(const t_ray ray, const t_cylinder cylinder,
								double *t);
void					find_closest_cylinder(t_data *data, const t_ray ray,
								double *t);
int						hit_any_cylinder(t_data *data, const t_ray ray,
								double t);
int						cylinder_normal(t_data *data);

#endif
