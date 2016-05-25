/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   describe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 22:38:26 by achazal           #+#    #+#             */
/*   Updated: 2016/03/08 22:38:32 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

void	describe_spheres(t_scene scene)
{
	unsigned int	i;

	write(1, SPHERES_INTRO, sizeof(SPHERES_INTRO) - 1);
	i = 0;
	while (i < scene.spheres_nb)
	{
		write(1, "\t", 1);
		vec3_describe(scene.spheres[i].center);
		dprintf(1, " %f %i", scene.spheres[i].r, scene.spheres[i].m);
		write(1, "\n", 1);
		++i;
	}
}
