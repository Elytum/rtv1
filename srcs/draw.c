#include <raytracer.h>
#include <mlx.h>
#include <mlx_macros.h>
#include <vec3.h>
#include <ray.h>
#include <math.h>

#define NAME "RTV1"
#define WIDTH 640
#define HEIGHT 480

#define MIN(a, b) ((a) > (b) ? b : a)

typedef struct	s_window
{
	void		*mlx_ptr;
	void		*mlx_win;
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

void			find_closest(t_scene scene, const t_ray ray, int *closest, float *t)
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
}

int				find_normal(const t_ray ray, const float t,
							t_vec3 *new_start, t_vec3 *n, t_vec3 center)
{
	float		temp;

	*new_start = vec3_add(ray.start, vec3_mult(ray.dir, t));
	*n = vec3_sub(*new_start, center);
	temp = vec3_dot(*n, *n);
	if (temp == 0)
		return (0);
	*n = vec3_mult(*n, 1.0f / sqrt(temp));
	return (1);
}

int				rgb_color(float r, float g, float b)
{
	return (((int)(255 * r) << 16) + ((int)(255 * g) << 8) + (int)(255 * b));
}

int				get_color(t_scene scene, int x, int y)
{
	t_ray		ray;
	int			closest[2];
	t_vec3		new_start;
	t_vec3		n;
	t_material	material;
	int			i;
	float		color[3];
	float		coef = 1.0f;
	int			level = 0;
	char		once = 1;

	while (once || (coef > 0.0f && level < 10))
	{
		once = 0;
		color[0] = 0;
		color[1] = 0;
		color[2] = 0;
		float t = 20000.0f;
		ray.start = vec3_new(x, y, -10000.0f);
		ray.dir = vec3_new(0, 0, 1);
		find_closest(scene, ray, closest, &t);
		if (closest[1] == -1)
			return (0x000000);
		if (!find_normal(ray, t, &new_start, &n, scene.spheres[closest[1]].center))
			return (0xFFFFFF);
		material = scene.materials[scene.spheres[closest[1]].m];
		i = 0;
		// HANDLE LIGHTS
		while (i < scene.lights_nb)
		{
			t_light	current = scene.lights[i];
			t_vec3	dist = vec3_sub(current.pos, new_start);

			if (vec3_dot(n, dist) <= 0.0f)
			{
				++i;
				continue ;
			}
			float	t = sqrt(vec3_dot(dist, dist));
			if (t <= 0.0f)
			{
				++i;
				continue ;
			}
			t_ray	light_ray;

			light_ray.start = new_start;
			light_ray.dir = vec3_mult(dist, 1.0f / t);
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
		float reflet = 2.0f * vec3_dot(ray.dir, n);
		ray.start = new_start;
		ray.dir = vec3_sub(ray.dir, vec3_mult(n, reflet));
		++level;
	}
	// dprintf(1, "%f %f %f\n", color[0] * 255 * 2550, color[1] * 255 * 2550, color[2] * 255 * 2550);
	return (rgb_color(MIN(color[0] * 255, 255), MIN(color[1] * 255, 255), MIN(color[2] * 255, 255)));
	(void)material;
	(void)new_start;
	(void)n;
}

void			raytrace(t_scene scene, t_window window)
{
	int			x;
	int			y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_pixel_put(window.mlx_ptr, window.mlx_win, x, y,
				get_color(scene, x, y));
			++x;
		}
		++y;
	}
	(void)scene;
}

void			draw_scene(t_scene scene)
{
	t_window	window;

	if ((window.mlx_ptr = mlx_init()) == NULL)
		return ;
	if ((window.mlx_win = mlx_new_window(window.mlx_ptr, WIDTH, HEIGHT, NAME)) == NULL)
		return ;
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