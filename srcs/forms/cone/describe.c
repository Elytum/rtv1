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

void	describe_cones(t_scene scene)
{
	unsigned int	i;

	write(1, CONES_INTRO, sizeof(PLANES_INTRO) - 1);
	i = 0;
	while (i < scene.cones_nb)
	{
		printf("\t(%f, %f, %f) (%f, %f, %f) %f %i\n",
				scene.cones[i].origin.x, scene.cones[i].origin.y,
					scene.cones[i].origin.z,
				scene.cones[i].dir.x, scene.cones[i].dir.y,
					scene.cones[i].dir.z,
				scene.cones[i].angle, scene.cones[i].m);
		++i;
	}
}
