#ifndef RAYTRACER_H
# define RAYTRACER_H

# include <unistd.h>
# include <forms.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <stdlib.h>

# include <ray.h>

# define FORMAT_INTRO "Wrong format: "
# define FORMAT_OUTRO " <OUTPUT FILE>\n"
# define OPEN_INTRO "Couldn't open file \""
# define OPEN_OUTRO "\"\n"
# define UNKNOWN "Unknown form, stopping\n"
# define VERBOSE 1
# define NAME "RTV1"
# define WIDTH 640
# define HEIGHT 480
# define MIN(a, b) (((a) < (b)) ? (a) : (b))
# define MAX(a,b) ((a) > (b) ? (a) : (b)) 

typedef struct			s_header
{
	float				camera_x;
	float				camera_y;
	float				camera_z;
	t_vec3				view;
	unsigned int		materials_nb;
	unsigned int		lights_nb;
	unsigned int		planes_nb;
	unsigned int		spheres_nb;
	unsigned int		cylinders_nb;
	unsigned int		cones_nb;
}						t_header;

typedef struct			s_scene
{
	float				camera_x;
	float				camera_y;
	float				camera_z;
	t_vec3				view;
	t_material			*materials;
	t_light				*lights;
	t_plane				*planes;
	t_sphere			*spheres;
	t_cylinder			*cylinders;
	t_cone				*cones;
	unsigned int		materials_nb;
	unsigned int		lights_nb;
	unsigned int		planes_nb;
	unsigned int		spheres_nb;
	unsigned int		cylinders_nb;
	unsigned int		cones_nb;
}						t_scene;

typedef struct			s_data
{
	t_scene				scene;
	t_ray				viewray;
	t_ray				lightray;
	int					closest[2];
	t_vec3				new_start;
	t_vec3				normal;
	t_material			material;
	float				color[3];
	double				coef;
	int					level;
	char				once;
	double				t;
}						t_data;

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

void					raytrace(t_data *data, t_window window);
int						get_color(t_data *data, int x, int y);
int						find_normal(const t_ray viewray, const float t,
							t_vec3 *new_start, t_vec3 *n, t_vec3 center);
int						rgb_color(int r, int g, int b);
void					init_scene(int fd, t_scene *scene);
void					delete_scene(t_scene scene);
void					describe_materials(t_scene scene);
void					describe_lights(t_scene scene);
void					describe_planes(t_scene scene);
void					describe_spheres(t_scene scene);
void					describe_cylinders(t_scene scene);
void					describe_cones(t_scene scene);
void					describe_scene(t_scene scene);
int						find_closest(t_data *data, const int get_normal);
int						solve_quadratic(double a, double b, double c, double *t);

#endif
