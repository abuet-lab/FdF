/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuet <abuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:22:04 by abuet             #+#    #+#             */
/*   Updated: 2026/04/09 14:28:02 by abuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	translate_iso(t_point t, t_sizetab *a)
{
	t_point	point;

	point.x = (t.y - t.x) * cos(a->angle * M_PI / 180.0)
		+ (((a->colone + a->line) * a->size_square * 0.866) / 2) + a->x;
	point.y = (t.y + t.x) * sin(a->angle * M_PI / 180.0) - t.z + 200;
	point.color = t.color;
	return (point);
}

t_point	dynamic_size(int x, int y, long ***map, t_sizetab *sizetab)
{
	t_point	point;

	point.color = map[x][y][1];
	if (sizetab->size_square == 0)
	{
		if (sizetab->line > sizetab->colone)
			sizetab->size_square = WITH / (sizetab->line * 2);
		else
			sizetab->size_square = HEIGHT / (sizetab->colone * 2);
		if (sizetab->size_square == 0)
			sizetab->size_square = 1;
	}
	point.x = x * sizetab->size_square;
	point.y = y * sizetab->size_square;
	if (sizetab->max_z == sizetab->min_z)
		point.z = 0;
	else
		point.z = map[x][y][0] * (150 / (sizetab->max_z - sizetab->min_z));
	return (point);
}

t_draw	fill_draw(t_point *s1, t_point *s2)
{
	t_draw	draw;

	draw.x1 = s1->x;
	draw.y1 = s1->y;
	draw.x2 = s2->x;
	draw.y2 = s2->y;
	draw.color = s1->color;
	return (draw);
}

void	put_pixel_bgra(t_mlx *mlx, int x, int y, unsigned int color_bgra)
{
	if (x < 0 || (x >= WITH) || y < 0 || y >= HEIGHT)
		return ;
	*(unsigned int *)(mlx->data + y * mlx->line_len + x * 4) = color_bgra;
}