/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 22:38:26 by achazal           #+#    #+#             */
/*   Updated: 2016/03/08 22:38:32 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include <raytracer.h>
# include <ray.h>

typedef struct s_data	t_data;

int		hit_plane(const t_ray ray, const t_plane sphere, double *t);
void	find_closest_plane(t_data *data, const t_ray ray, double *t);
int		hit_any_plane(t_data *data, const t_ray ray, double t);
int		plane_normal(t_data *data);

#endif
