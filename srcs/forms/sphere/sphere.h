/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 22:38:26 by achazal           #+#    #+#             */
/*   Updated: 2016/03/08 22:38:32 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include <raytracer.h>
# include <ray.h>

typedef struct s_data	t_data;

typedef struct			s_sphere
{
	t_vec3				center;
	double				r;
	int					m;
}						t_sphere;

int						hit_sphere(const t_ray ray, const t_sphere sphere,
							double *t);
int						sphere_normal(t_data *data);
void					find_closest_sphere(t_data *data, const t_ray ray,
							double *t);
int						hit_any_sphere(t_data *data, const t_ray ray, double t);

#endif
