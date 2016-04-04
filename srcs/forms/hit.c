#include <forms.h>

int				find_closest(t_data *data, const int get_normal)
{
	// int			ret;

	data->closest[1] = -1;
	if (get_normal == 1)
	{
		find_closest_sphere(data, data->viewray, &(data->t));
		find_closest_plane(data, data->viewray, &(data->t));
		find_closest_cone(data, data->viewray, &(data->t));
		find_closest_cylinder(data, data->viewray, &(data->t));
		// printf("%i %i\n", data->closest[0], data->closest[1]);
		if (data->closest[1] == -1)
			return (0);
		if (data->closest[0] == SPHERE)
			return (sphere_normal(data));
		else if (data->closest[0] == PLANE)
			return (plane_normal(data));
		return (1);
	}
	else
	{
		return (0);
		// ret = hit_any_plane(data, data->viewray, 0);
		// if (ret != 1)
		// 	printf("Ret: %i\n", ret);
		// return (ret);
	}
}