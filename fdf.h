/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinebuet <antoinebuet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 10:37:03 by antoinebuet       #+#    #+#             */
/*   Updated: 2026/04/09 12:55:20 by antoinebuet      ###   ########.fr       */
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

# define WITH	1000
# define HEIGHT	1000

long int ***parse_map(char *file_name, t_sizetab *sizetab);

#endif