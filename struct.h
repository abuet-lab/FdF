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

#endif