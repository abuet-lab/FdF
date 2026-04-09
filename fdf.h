/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinebuet <antoinebuet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 10:37:03 by antoinebuet       #+#    #+#             */
/*   Updated: 2026/04/09 14:47:01 by antoinebuet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "keys.h"
# include "libft/get_next_line/get_next_line.h"
# include "libft/libft.h"
# include "struct.h"
# include "linked_list.h"
# include <math.h>
# ifdef __APPLE__
#  include "./minilibx_macos/mlx.h"
# else
#  include "./minilibx-linux/mlx.h"
# endif

# define WITH	1500
# define HEIGHT	1500
# ifndef M_PI
#  define M_PI 3.14159265359
# endif

long int		***parse_map(char *file_name, t_sizetab *sizetab);

int				find_max(long ***tab_parse, t_sizetab *sizetab);
int				find_min(long ***tab_parse, t_sizetab *sizetab);

int				verif_name(char *file_name);
int				count_number(char **first_split);
int				put_hex(char *hexa);
int				verif_line(char **first_split, t_firstsplit *t);

void			free_list(t_node **list);
void			free_tab33(long int ***final_tab, t_firstsplit *t);
void			free_tab22(char **array);
void			free_final_tab(long int **final_tab);
long int		**malloc_final_tab(char **first_split, t_sizetab *sizetab);

int				handle_close(void *param);
void			zoom(int keycode, t_data *data);
void			translate(int keycode, t_data *data);
void			rotate(int keycode, t_data *data);
int				handle_expose(void *param);

t_point			translate_iso(t_point t, t_sizetab *a);
t_point			dynamic_size(int x, int y, long ***map, t_sizetab *sizetab);
t_draw			fill_draw(t_point *s1, t_point *s2);
void			put_pixel_bgra(t_mlx *mlx, int x, int y,
					unsigned int color_bgra);

void			draw_landscape(t_mlx *mlx, long ***map, t_sizetab *sizetab);

#endif