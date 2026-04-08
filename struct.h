#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_mlx
{
	void *mlx;
    void *win;
    void *img;
    char *data;
    int bpp; 
	int	line_len;
	int endian;
}	t_mlx;

typedef struct s_node
{
	char *value;
	struct s_node *next;
}	t_node;

typedef struct s_fisrtsplit
{
	int i;
	int line;
}	t_firstsplit;

typedef struct s_draw
{
	int x1;
	int y1;
	int x2;
	int y2;
	int color;
}	t_draw;

typedef struct s_point
{
	int x;
	int y;
	int z;
	int color;
}	t_point;

typedef struct s_sizetab
{
	int line;
	int colone;
	int min_z;
	int max_z;
	int size_square;
	int angle;
	int x;
	int y;
}	t_sizetab;

typedef struct s_square
{
	t_point s1;
	t_point s2;
	t_point s3;
	t_point s4;
}	t_square;

typedef struct s_drawline
{
	float	delta_x;
	float	delta_y;
	float	steps;
	float	inc_x;
	float	inc_y;
	float	x;
	float	y;
	int		i;
}	t_drawline;

typedef struct s_data
{
	t_mlx	mlx;
	long int ***map;
	t_sizetab sizetab;
}	t_data;
#endif