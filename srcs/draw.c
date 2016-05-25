#include <raytracer.h>
#include <mlx.h>
#include <mlx_macros.h>
#include <vec3.h>
#include <ray.h>
#include <math.h>
#include <forms.h>
#include <float.h>


int				find_normal(const t_ray viewray, const float t,
							t_vec3 *new_start, t_vec3 *n, t_vec3 center)
{
	float		temp;

	*new_start = vec3_add(viewray.start, vec3_mult(viewray.dir, t));
	*n = vec3_sub(*new_start, center);
	temp = vec3_dot(*n, *n);
	if (temp == 0.0f)
		return (0);
	*n = vec3_mult(*n, 1.0f / sqrt(temp));
	return (1);
}

int				rgb_color(int r, int g, int b)
{
	return ((r << 16) + (g << 8) + b);
}

void			init_data(t_data *data, int x, int y)
{
	t_vec3		target = vec3_norm(vec3_new(x - WIDTH / 2, y - HEIGHT / 2, - (WIDTH / 2 * tan(30 / 2))));
	// const t_vec3	pos = vec3_new(data->scene.camera_x, data->scene.camera_y, data->scene.camera_z);

	data->color[0] = 0;
	data->color[1] = 0;
	data->color[2] = 0;
	data->coef = 1.0f;
	data->level = 0;
	data->once = 1;
	data->viewray.start = vec3_new(data->scene.camera_x, data->scene.camera_y, data->scene.camera_z);
	// data->viewray.dir = vec3_new(0.0f, 0.0f, 1.0f);
	// data->viewray.dir = vec3_norm(vec3_sub(target, pos));
	target = vec3_rotx(target, data->scene.view.x);
	target = vec3_roty(target, data->scene.view.y);
	target = vec3_rotz(target, data->scene.view.z - 1);
	data->viewray.dir = vec3_norm(target);//vec3_norm(vec3_new(fmod(target.x + data->scene.view.x, 3.14), fmod(target.y + data->scene.view.y, 3.14), target.z));
}

int				get_color(t_data *data, int x, int y)
{
	unsigned int	i;

	// Init data structure
	init_data(data, x, y);
	// As long as the ray can resbound
	while (data->once || (data->coef > 0.0f && data->level < 2))
	{
		// We rememver we at least resbounded once
		data->once = 0;
		// We set the farest distance to 20000
		data->t = DBL_MAX;
		// If there is nothine closer, stop
		if (!find_closest(data, 1))
			break ;

// data->color[0] += data->material.r;
// data->color[1] += data->material.g;
// data->color[2] += data->material.b;

double reflet = 2.0f * vec3_dot(data->viewray.dir, data->normal);
		// Else, handle it's color
		i = 0;
		// For every lights in the scene
		while (i < data->scene.lights_nb)
		{
			t_light		current = data->scene.lights[i];
			t_vec3		dist = vec3_sub(current.pos, data->new_start);

			// If the light is perpendicular to the pixel, ignore it
			if (vec3_dot(data->normal, dist) <= 0.0f)
			{
				++i;
				continue ;
			}
			data->t = sqrt(vec3_dot(dist, dist));
			// Or if the light is on the other side of the pixel, ignore it
			if (data->t <= 0.0f)
			{
				++i;
				continue ;
			}
			// Else, create a new ray
			data->lightray.start = data->new_start;
			data->lightray.dir = vec3_mult(dist, 1 / data->t);
			// And if that ray doesn't cross anything between the actual point and the light's position
			if (!find_closest(data, 0))
			{
				// Add it's color
				double lambert = vec3_dot(data->lightray.dir, data->normal) * data->coef;
				data->color[0] += lambert * current.r * data->material.r;
				data->color[1] += lambert * current.g * data->material.g;
				data->color[2] += lambert * current.b * data->material.b;

				t_vec3 R = vec3_sub(data->lightray.dir, vec3_mult(data->normal, 2 * vec3_dot(data->lightray.dir, data->normal)));
				double dot = vec3_dot(data->viewray.dir, R);
				if (dot > 0)
				{
					double ratio = 1 * pow(dot, 20);
					data->color[0] += ratio * current.r;
					data->color[1] += ratio * current.g;
					data->color[2] += ratio * current.b;
				}
			}
			// else
			// {
			// 	printf("Hidden\n");
			// }
			++i;
		}
		data->coef *= data->material.c;
		data->viewray.start = data->new_start;
		data->viewray.start = data->new_start;
		data->viewray.dir = vec3_sub(data->viewray.dir, vec3_mult(data->normal, reflet));
		++data->level;
	}
	return (rgb_color(MIN(data->color[0] * 255.0f, 255.0f), MIN(data->color[1] * 255.0f, 255.0f), MIN(data->color[2] * 255.0f, 255)));
}

// void			raytrace(t_data *data, t_window window)
// {
// 	int			x;
// 	int			y;
// 	int			color;
// 	char		*ptr;
// 	int			*cast;

// 	while (42)
// 	{
// 		ptr = window.data;
// 		y = 0;
// 		while (y < HEIGHT)
// 		{
// 			x = 0;
// 			while (x < WIDTH)
// 			{
// 				color = get_color(data, x, y);
// 				cast = (int *)ptr;
// 				*cast = color;
// 				++x;
// 				ptr += 4;
// 			}
// 			++y;
// 		}
// 		mlx_put_image_to_window(window.mlx_ptr, window.mlx_win, window.img, 0, 0);
// 		mlx_do_sync(window.mlx_ptr);
// 	}
// }

void			draw_scene(t_data *data)
{
	t_window	window;

	if ((window.mlx_ptr = mlx_init()) == NULL)
		return ;
	if ((window.mlx_win = mlx_new_window(window.mlx_ptr, WIDTH, HEIGHT, NAME)) == NULL)
		return ;
	window.img = mlx_new_image(window.mlx_ptr, WIDTH, HEIGHT);
	window.data = mlx_get_data_addr(window.img, &(window.bpp),
		&(window.line_size), &(window.endian));
	raytrace(data, window);
	mlx_destroy_window(window.mlx_ptr, window.mlx_win);
}

int		main(int ac, char **av)
{
	t_data		*data;
	int			fd;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (0);
	if (ac != 2)
	{
		write(2, FORMAT_INTRO, sizeof(FORMAT_INTRO) - 1);
		write(2, av[0], strlen(av[0]));
		write(2, FORMAT_OUTRO, sizeof(FORMAT_OUTRO) - 1);
		return (1);
	}
	if ((fd = open(av[1], O_RDONLY | O_CREAT)) == -1)
	{
		write(2, OPEN_INTRO, sizeof(OPEN_INTRO) - 1);
		write(2, av[1], strlen(av[1]));
		write(2, OPEN_OUTRO, sizeof(OPEN_OUTRO) - 1);
		return (1);
	}
	init_scene(fd, &(data->scene));
	close(fd);
	if (VERBOSE)
		describe_scene(data->scene);
	draw_scene(data);
	delete_scene(data->scene);
	free(data);
	return (0);
}