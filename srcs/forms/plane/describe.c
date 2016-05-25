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

void	describe_planes(t_scene scene)
{
	unsigned int	i;

	write(1, PLANES_INTRO, sizeof(PLANES_INTRO) - 1);
	i = 0;
	while (i < scene.planes_nb)
	{
		printf("\t(%f, %f, %f) (%f, %f, %f)\n", scene.planes[i].normal.x,
			scene.planes[i].normal.y, scene.planes[i].normal.z,
			scene.planes[i].coord.x, scene.planes[i].coord.y,
			scene.planes[i].coord.z);
		++i;
	}
}
