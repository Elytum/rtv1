/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 22:38:26 by achazal           #+#    #+#             */
/*   Updated: 2016/03/08 22:38:32 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_H
# define CONE_H

# include <raytracer.h>
# include <ray.h>

typedef struct			s_cone
{
	t_vec3				origin;
	t_vec3				dir;
	float				angle;
	int					m;
}						t_cone;

typedef struct s_data	t_data;

int						hit_cone(const t_ray ray, const t_cone cone,
							double *t);
void					find_closest_cone(t_data *data, const t_ray ray,
							double *t);
int						hit_any_cone(t_data *data, const t_ray ray, double t);
int						cone_normal(t_data *data);

#endif
