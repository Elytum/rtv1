#include <raytracer.h>
#include <mlx.h>
#include <mlx_macros.h>
#include <vec3.h>
#include <ray.h>
#include <math.h>

#define NAME "RTV1"
#define WIDTH 640
#define HEIGHT 480

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef struct	s_window
{
	void		*mlx_ptr;
	void		*mlx_win;
	void		*img;
	char		*data;
	int			bpp;
	int			line_size;
	int			endian;
}				t_window;

typedef enum	s_form
{
	PLAN = 0,
	SPHERE,
	CYLINDER,
	CONE
}				t_form;

int				hit_sphere(const t_ray ray, const t_sphere sphere, float *t)
{
	t_vec3		dist;
	float		b;
	float		d;
	float		t0;
	float		t1;
	int			ret;

	dist = vec3_sub(sphere.center, ray.start);
	b = vec3_dot(ray.dir, dist);
	d = b * b - vec3_dot(dist, dist) + sphere.r * sphere.r;
	t0 = b - sqrt(d);
	t1 = b + sqrt(d);
	ret = 0;
	if (t0 > 0.1f && t0 < *t)
	{
		*t = t0;
		ret = 1;
	}
	if (t1 > 0.1f && t1 < *t)
	{
		*t = t1;
		ret = 1;
	}
	return (ret);
}

int				find_closest(t_scene scene, const t_ray ray, int *closest, float *t)
{
	int			i;

	closest[1] = -1;
	i = 0;
	while (i < scene.spheres_nb)
	{
		if (hit_sphere(ray, scene.spheres[i], t))
		{
			closest[0] = SPHERE;
			closest[1] = i;
		}
		++i;
	}
	return (closest[1] != -1);
}

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

int				get_color(t_scene scene, int x, int y)
{
	t_ray		viewray;
	int			closest[2];
	t_vec3		new_start;
	t_vec3		n;
	t_material	material;
	int			i;
	float		color[3];
	float		coef;
	int			level;
	char		once;

	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	coef = 1.0f;
	level = 0;
	once = 1;
	viewray.start = vec3_new(x - scene.camera_x, y - scene.camera_y, -10000.0f - scene.camera_z);
	viewray.dir = vec3_new(0.0f, 0.0f, 1.0f);
	while (once || (coef > 0.0f && level < 10))
	{
						// vec3_describe(viewray.start);
						// write(1, ", ", 2);
						// vec3_describe(viewray.dir);
						// write(1, "\n", 1);
		once = 0;
		float t = 20000.0f;
		if (!find_closest(scene, viewray, closest, &t) ||
			!find_normal(viewray, t, &new_start, &n, scene.spheres[closest[1]].center))
			break ;
		material = scene.materials[scene.spheres[closest[1]].m];
		i = 0;
		// HANDLE LIGHTS
		while (i < scene.lights_nb)
		{
			t_light		current = scene.lights[i];
			t_vec3		dist = vec3_sub(current.pos, new_start);

			if (vec3_dot(n, dist) <= 0.0f)
			{
				++i;
				continue ;
			}
			t = sqrt(vec3_dot(dist, dist));
			if (t <= 0.0f)
			{
				++i;
				continue ;
			}
			t_ray	light_ray;

			light_ray.start = new_start;
			light_ray.dir = vec3_mult(dist, 1 / t);
			// HANDLE SHADOWS
			char	inShadow = 0;

			int c;
			c = 0;
			while (c < scene.spheres_nb)
			{
				if (hit_sphere(light_ray, scene.spheres[c], &t))
				{
					inShadow = 1;
					break;
				}
				++c;
			}
			if (!inShadow)
			{
				float lambert = vec3_dot(light_ray.dir, n) * coef;
				color[0] += lambert * current.r * material.r;
				color[1] += lambert * current.g * material.g;
				color[2] += lambert * current.b * material.b;
			}
			++i;
		}
		coef *= material.c;
		float reflet = 2.0f * vec3_dot(viewray.dir, n);
		viewray.start = new_start;
		viewray.dir = vec3_sub(viewray.dir, vec3_mult(n, reflet));
		++level;
	}
	return (rgb_color(MIN(color[0] * 255.0f, 255.0f), MIN(color[1] * 255.0f, 255.0f), MIN(color[2] * 255.0f, 255)));
}

#define MAX_SQUARE 1

void			draw_square(t_window window, char *ptr, int size, int color)
{
	int			i;
	int			j;
	char		*next;
	int			*cast;

	i = 0;
	while (i < size)
	{
		j = 0;
		next = ptr + window.line_size;
		cast = (int *)ptr;
		while (j < size)
		{
			*cast++ = color;
			++j;
		}
		ptr = next;
		++i;
	}
}

int				do_draw_square(int x, int y, int size)
{
	if (size == MAX_SQUARE || x % (size * 2) || y % (size * 2))
		return (1);
	return (0);
}

void			raytrace_huge(t_scene scene, t_window window, int size)
{
	int			x;
	int			y;
	int			color;
	char		*ptr;
	const int	step = size * window.bpp / 8;

	ptr = window.data;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (do_draw_square(x, y, size))
			{
				color = get_color(scene, x, y);
				draw_square(window, ptr, size, color);
			}
			x += size;
			ptr += step;
		}
		y += size;
		ptr += (size - 1) * (window.line_size);
	}
	mlx_put_image_to_window(window.mlx_ptr, window.mlx_win, window.img, 0, 0);
}

void			raytrace(t_scene scene, t_window window)
{
	// while (1)
	// {
		int		size;

		size = MAX_SQUARE;
		while (size)
		{
			raytrace_huge(scene, window, size);
			size /= 2;
		}
		// scene.camera_x += 10;
	// 	scene.camera_y += 5;
	// }
}

void			draw_scene(t_scene scene)
{
	t_window	window;

	if ((window.mlx_ptr = mlx_init()) == NULL)
		return ;
	if ((window.mlx_win = mlx_new_window(window.mlx_ptr, WIDTH, HEIGHT, NAME)) == NULL)
		return ;
	window.img = mlx_new_image(window.mlx_ptr, WIDTH, HEIGHT);
	window.data = mlx_get_data_addr(window.img, &(window.bpp),
		&(window.line_size), &(window.endian));
	raytrace(scene, window);
	// mlx_hook(window.mlx_win, KEYPRESS, KEYPRESSMASK, key_press, &window);
	// mlx_loop_hook(window.mlx_ptr, refresh, &window);
	// mlx_loop(window.mlx_ptr);
	sleep(42);
	mlx_destroy_window(window.mlx_ptr, window.mlx_win);
	(void)scene;
}

int		main(int ac, char **av)
{
	t_scene		scene;
	int			fd;

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
	init_scene(fd, &scene);
	close(fd);
	if (VERBOSE)
		describe_scene(scene);
	draw_scene(scene);
	delete_scene(scene);
	return (0);
}