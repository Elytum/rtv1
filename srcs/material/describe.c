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

void	describe_materials(t_scene scene)
{
	unsigned int	i;

	write(1, MATERIALS_INTRO, sizeof(MATERIALS_INTRO) - 1);
	i = 0;
	while (i < scene.materials_nb)
	{
		printf("\t[%f, %f, %f] %f\n", scene.materials[i].r,
				scene.materials[i].g, scene.materials[i].b,
				scene.materials[i].c);
		++i;
	}
}
