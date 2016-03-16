#ifndef MLX_DATA_H
# define MLX_DATA_H

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

#endif