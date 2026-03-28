/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinebuet <antoinebuet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:42:31 by antoinebuet       #+#    #+#             */
/*   Updated: 2026/03/28 21:04:23 by antoinebuet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "struct.h"

// static void	put_pixel_bgra(t_mlx *mlx, int x, int y, unsigned int color_bgra)
// {
// 	*(unsigned int *)(mlx->data + y * mlx->line_len + x * 4) = color_bgra;
// }

// void draw_line(t_mlx *mlx, int x1, int y1, int x2, int y2, unsigned int color_bgra)
// {
// 	float delta_x;
// 	float coef_dir;
// 	int x;

// 	delta_x = x2 - x1;
// 	coef_dir = (float)(y2 - y1) / delta_x;
// 	x = x1;
// 	if (delta_x == 0)
// 	{
// 		if (y1 > y2)
// 		{
// 			x = y1;
// 			y1 = y2;
// 			y1 = x;
// 		}
// 		while(y1 <= y2)
// 		{
// 			put_pixel_bgra(mlx, x1, y1, color_bgra);
// 			y1++;
// 		}
// 	}	
// 	else if (delta_x > 0)
// 	{
// 		while (x <= x2)
// 		{
// 			put_pixel_bgra(mlx, x,(int)(y1 + (x - x1) * coef_dir), color_bgra);
// 			x++;
// 		}
// 	}
// 	else if (delta_x < 0)
// 	{
// 		while (x >= x2)
// 		{
// 			put_pixel_bgra(mlx, x,(int)(y1 + (x - x1) * coef_dir), color_bgra);
// 			x--;
// 		}
// 	}
// }

// static int *translate_iso(int x, int y, int z)
// {
// 	int *iso;

// 	iso = malloc(2 * sizeof(int));
// 	if (!iso)
// 		return (0);
// 	iso[0] = (x - y) * cos(30 * M_PI / 180.0); //x iso
// 	iso[1] = (x + y) * sin(30 * M_PI / 180.0) - z; //y iso
// 	return (iso);
// }

// void init_grille(t_mlx *mlx, int size_carre, int color, int number_x, int number_y)
// {
// 	int *iso;
// 	int x;
// 	int y;
// 	int count1;
// 	int count2;
// 	int i;

// 	count2 = 0;
// 	i = number_x;
// 	while (number_y > 0)
// 	{
// 		i = number_x;
// 		x = 0;
// 		y = 0;
// 		count1 = 0;
// 		while (i > 0)
// 		{
// 			while (x < size_carre)
// 			{
// 				iso = translate_iso(x, y, 0);
// 				iso[0] +=(int) (400 - (count2 * (size_carre * 0.866))) + (count1 * (size_carre * 0.866));
// 		 		iso[1] += (int) (count2 * size_carre * 0.5) + (count1 * (size_carre * 0.5));
//     			put_pixel_bgra(mlx, iso[0], iso[1], color);
// 				free(iso);
// 				x++;
// 			}
// 			while (y < size_carre)
// 			{
// 				iso = translate_iso(x, y, 0);
//     			iso[0] +=(int) (400 - (count2 * (size_carre * 0.866))) + (count1 * (size_carre * 0.866));
// 		 		iso[1] += (int) (count2 * size_carre * 0.5) + (count1 * (size_carre * 0.5));
//     			put_pixel_bgra(mlx, iso[0], iso[1], color);
// 				free(iso);
// 				iso = NULL;
// 				y++;
// 			}
// 			while (x > 0)
// 			{
// 				iso = translate_iso(x, y, 0);
//     			iso[0] +=(int) (400 - (count2 * (size_carre * 0.866))) + (count1 * (size_carre * 0.866));
// 		 		iso[1] += (int) (count2 * size_carre * 0.5) + (count1 * (size_carre * 0.5));
//     			put_pixel_bgra(mlx, iso[0], iso[1], color);
// 				free(iso);
// 				iso = NULL;
// 				x--;
// 			}
// 			while (y > 0)
// 			{
// 				iso = translate_iso(x, y, 0);
//     			iso[0] +=(int) (400 - (count2 * (size_carre * 0.866))) + (count1 * (size_carre * 0.866));
// 		 		iso[1] += (int) (count2 * size_carre * 0.5) + (count1 * (size_carre * 0.5));
//     			put_pixel_bgra(mlx, iso[0], iso[1], color);
// 				free(iso);
// 				iso = NULL;
// 				y--;
// 			}
// 			count1++;
// 			i--;
// 		}
// 		number_y--;
// 		count2++;
// 	}
// }

int main(int argc, char **argv)
{
	//t_mlx	mlx;
	//int size_carre = 20;
	int ***map;
	int i = 0;
	int j;
	if (argc != 2)
		return (0);
	map = parse_map(argv[1]);
	if (!map)
		return (0);
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			printf(" | %d, ", map[i][j][0]);
			printf("%x", map[i][j][1]);
			j++;
		}
		printf("\n");
		i++;
	}
	// mlx.mlx = mlx_init();
	// mlx.win = mlx_new_window(mlx.mlx, 800, 600, "Test");
	// mlx.img = mlx_new_image(mlx.mlx, 800, 600);
	// mlx.data = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.line_len, &mlx.endian);
	//init_grille(&mlx, size_carre, 0x00FFFF, 20, 10);
	// mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	// mlx_loop(mlx.mlx);
}
