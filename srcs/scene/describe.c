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

void	describe_scene(t_scene scene)
{
	printf("Camera: (%f, %f, %f) (%f, %f, %f)\nNumber of materials: %i\n\
		Number of lights: %i\nNumber of planes: %i\nNumber of spheres: %i\n\
		Number of cylinders: %i\nNumber of cones: %i\n\n",
		scene.camera_x, scene.camera_y, scene.camera_z, scene.view.x,
		scene.view.y, scene.view.z,
		scene.materials_nb, scene.lights_nb, scene.planes_nb,
		scene.spheres_nb, scene.cylinders_nb, scene.cones_nb);
	if (scene.materials_nb)
		describe_materials(scene);
	if (scene.lights_nb)
		describe_lights(scene);
	if (scene.planes_nb)
		describe_planes(scene);
	if (scene.spheres_nb)
		describe_spheres(scene);
	if (scene.cylinders_nb)
		describe_cylinders(scene);
	if (scene.cones_nb)
		describe_cones(scene);
}
