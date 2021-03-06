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

void	describe_cylinders(t_scene scene)
{
	unsigned int	i;

	write(1, CYLINDERS_INTRO, sizeof(CYLINDERS_INTRO) - 1);
	i = 0;
	while (i < scene.cylinders_nb)
	{
		printf("\t(%f, %f, %f) (%f, %f, %f) %f %i\n",
				scene.cylinders[i].origin.x, scene.cylinders[i].origin.y,
				scene.cylinders[i].origin.z, scene.cylinders[i].dir.x,
				scene.cylinders[i].dir.y, scene.cylinders[i].dir.z,
				scene.cylinders[i].r, scene.cylinders[i].m);
		++i;
	}
}
